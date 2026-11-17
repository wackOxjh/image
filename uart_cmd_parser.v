`timescale 1ns / 1ps

module uart_cmd_parser #(
    parameter CLK_DIV = 868 // 100MHz -> 115200 baud
)(
    input         clk,
    input         rst_n,
    input         uart_rx,
    output        uart_tx,
    output [23:0] freq_k,       // DDS frequency control word
    output [7:0]  amp,            // DAC amplitude (4~41 maps to 80~800 mV)
    output reg    data_update     // One-cycle pulse when confirm button pressed
);

// ======================
// Hard limits
// ======================
localparam FREQ_MIN = 32'd100;
localparam FREQ_MAX = 32'd20000;
localparam AMP_MIN  = 16'd80;
localparam AMP_MAX  = 16'd800;

// freq_k ~= freq_hz * 2^24 / 100e6  =>  43/256
localparam FREQ_SCALE = 8'd43;
localparam FREQ_SHIFT = 4'd8;

// amp ~= mv * 255 / 5000  =>  13/256
localparam AMP_SCALE  = 8'd13;
localparam AMP_SHIFT  = 4'd8;

// Send FSM states
localparam ST_IDLE      = 3'd0;
localparam ST_FREQ_PREP  = 3'd1;
localparam ST_FREQ_DIG   = 3'd2;
localparam ST_FREQ_PACK  = 3'd3;
localparam ST_TX         = 3'd4;
localparam ST_AMP_PREP   = 3'd5;
localparam ST_AMP_DIG    = 3'd6;
localparam ST_AMP_PACK   = 3'd7;

// ======================
// UART RX
// ======================
reg [15:0] clk_cnt;
reg [3:0]  bit_cnt;
reg [7:0]  rx_data;
reg        rx_busy;
reg        rx_done;
reg        uart_rx_d1, uart_rx_d2;

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        uart_rx_d1 <= 1'b1;
        uart_rx_d2 <= 1'b1;
    end else begin
        uart_rx_d1 <= uart_rx;
        uart_rx_d2 <= uart_rx_d1;
    end
end

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        clk_cnt <= 16'd0;
        bit_cnt <= 4'd0;
        rx_busy <= 1'b0;
        rx_done <= 1'b0;
        rx_data <= 8'd0;
    end else begin
        rx_done <= 1'b0;
        if (!rx_busy && !uart_rx_d2) begin
            rx_busy <= 1'b1;
            clk_cnt <= CLK_DIV / 2;
            bit_cnt <= 4'd0;
        end else if (rx_busy) begin
            if (clk_cnt == CLK_DIV - 1) begin
                clk_cnt <= 16'd0;
                if (bit_cnt == 4'd8) begin
                    rx_done <= 1'b1;
                    rx_busy <= 1'b0;
                end else begin
                    rx_data[bit_cnt] <= uart_rx_d2;
                    bit_cnt <= bit_cnt + 4'd1;
                end
            end else begin
                clk_cnt <= clk_cnt + 16'd1;
            end
        end
    end
end

// ======================
// Frame parser (footer: 3 x 0xFF)
// ======================
reg [7:0]  rx_buf [0:15];
reg [3:0]  rx_buf_ptr;
reg        frame_done;

reg [31:0] freq_num;
reg [15:0] amp_num;

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rx_buf_ptr <= 4'd0;
        frame_done <= 1'b0;
        freq_num <= 32'd1000;
        amp_num <= 16'd400;
        data_update <= 1'b0;
    end else begin
        frame_done <= 1'b0;
        data_update <= 1'b0;

        if (rx_done) begin
            rx_buf[rx_buf_ptr] <= rx_data;
            rx_buf_ptr <= rx_buf_ptr + 4'd1;

            if (rx_buf_ptr >= 4'd2 &&
                rx_buf[rx_buf_ptr - 4'd2] == 8'hFF &&
                rx_buf[rx_buf_ptr - 4'd1] == 8'hFF &&
                rx_data == 8'hFF) begin
                frame_done <= 1'b1;
                rx_buf_ptr <= 4'd0;

                if (rx_buf[0] == 8'h05 && rx_buf[1] == 8'h05 && rx_buf[2] == 8'h01)
                    data_update <= 1'b1;

                if (rx_buf[0] == 8'h13 && rx_buf[1] == 8'h03)
                    freq_num <= {rx_buf[5], rx_buf[4], rx_buf[3], rx_buf[2]};

                if (rx_buf[0] == 8'h13 && rx_buf[1] == 8'h04)
                    amp_num <= {rx_buf[3], rx_buf[2]};
            end
        end

        if (rx_buf_ptr >= 4'd15)
            rx_buf_ptr <= 4'd0;
    end
end

// ======================
// Clamp + scale (2-stage pipeline)
// ======================
reg [31:0] freq_calc_in;
reg [15:0] amp_calc_in;
reg [31:0] freq_send;
reg [15:0] amp_send;
reg [23:0] freq_k_reg;
reg [7:0]  amp_reg;

wire [31:0] freq_clamped =
    (freq_num < FREQ_MIN) ? FREQ_MIN :
    (freq_num > FREQ_MAX) ? FREQ_MAX : freq_num;

wire [15:0] amp_clamped =
    (amp_num < AMP_MIN) ? AMP_MIN :
    (amp_num > AMP_MAX) ? AMP_MAX : amp_num;

wire [39:0] freq_mult = freq_calc_in * 40'd43;
wire [23:0] freq_mult_shifted = freq_mult[31:8];
wire [23:0] amp_mult = amp_calc_in * AMP_SCALE;
wire [7:0]  amp_scaled = amp_mult[15:8];

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        freq_calc_in <= 32'd1000;
        amp_calc_in  <= 16'd400;
        freq_send    <= 32'd1000;
        amp_send     <= 16'd400;
    end else begin
        freq_calc_in <= freq_clamped;
        amp_calc_in  <= amp_clamped;
        freq_send    <= freq_calc_in;
        amp_send     <= amp_calc_in;
    end
end

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        freq_k_reg <= 24'd17;
        amp_reg    <= 8'd20;
    end else begin
        freq_k_reg <= freq_mult_shifted;
        amp_reg    <= amp_scaled;
    end
end

// ======================
// UART TX bit engine
// ======================
reg [15:0] tx_clk_cnt;
reg [3:0]  tx_bit_cnt;
reg [9:0]  tx_shift_reg;
reg        tx_busy;
reg        tx_en;
reg [7:0]  tx_data;

(* IOB = "TRUE" *) reg uart_tx_reg;

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        tx_clk_cnt <= 16'd0;
        tx_bit_cnt <= 4'd0;
        tx_shift_reg <= 10'h3FF;
        tx_busy <= 1'b0;
    end else begin
        if (tx_en && !tx_busy) begin
            tx_busy <= 1'b1;
            tx_shift_reg <= {1'b1, tx_data, 1'b0};
            tx_clk_cnt <= 16'd0;
            tx_bit_cnt <= 4'd0;
        end else if (tx_busy) begin
            if (tx_clk_cnt == CLK_DIV - 1) begin
                tx_clk_cnt <= 16'd0;
                if (tx_bit_cnt == 4'd10)
                    tx_busy <= 1'b0;
                else begin
                    tx_shift_reg <= {1'b1, tx_shift_reg[9:1]};
                    tx_bit_cnt <= tx_bit_cnt + 4'd1;
                end
            end else begin
                tx_clk_cnt <= tx_clk_cnt + 16'd1;
            end
        end
    end
end

always @(posedge clk or negedge rst_n) begin
    if (!rst_n)
        uart_tx_reg <= 1'b1;
    else
        uart_tx_reg <= tx_shift_reg[0];
end

// ======================
// Reply FSM (multi-cycle digit conversion)
// ======================
reg [2:0]  send_state;
reg [31:0] freq_num_prev;
reg [15:0] amp_num_prev;

reg [15:0] bcd_temp;
reg [15:0] amp_bcd_temp;
reg [2:0]  digit_idx;

reg [7:0]  freq_digit [0:4];
reg [7:0]  amp_digit  [0:2];
reg [7:0]  send_buf [0:15];
reg [3:0]  send_cnt;
reg [3:0]  send_len;

wire [3:0]  freq_digit_val = bcd_temp % 16'd10;
wire [15:0] bcd_next       = bcd_temp / 16'd10;

wire [3:0]  amp_digit_val  = amp_bcd_temp % 16'd10;
wire [15:0] amp_bcd_next   = amp_bcd_temp / 16'd10;

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        freq_num_prev <= 32'd1000;
        amp_num_prev  <= 16'd400;
        send_state    <= ST_IDLE;
        bcd_temp      <= 16'd0;
        amp_bcd_temp  <= 16'd0;
        digit_idx     <= 3'd0;
        send_cnt      <= 4'd0;
        send_len      <= 4'd0;
        tx_en         <= 1'b0;
    end else begin
        freq_num_prev <= freq_num;
        amp_num_prev  <= amp_num;
        tx_en         <= 1'b0;

        case (send_state)
            ST_IDLE: begin
                if ((freq_num != freq_num_prev) ||
                    (amp_num != amp_num_prev) ||
                    data_update) begin
                    send_state <= ST_FREQ_PREP;
                end
            end

            // One decimal digit per clock (/10). Max freq is 20000, 16-bit temp is enough.
            ST_FREQ_PREP: begin
                bcd_temp  <= freq_send[15:0];
                digit_idx <= 3'd4;
                send_state <= ST_FREQ_DIG;
            end

            ST_FREQ_DIG: begin
                freq_digit[digit_idx] <= freq_digit_val + 8'h30;
                bcd_temp <= bcd_next;
                if (digit_idx == 3'd0)
                    send_state <= ST_FREQ_PACK;
                else
                    digit_idx <= digit_idx - 3'd1;
            end

            ST_FREQ_PACK: begin
                send_buf[0]  <= 8'h6E;
                send_buf[1]  <= 8'h30;
                send_buf[2]  <= 8'h2E;
                send_buf[3]  <= 8'h76;
                send_buf[4]  <= 8'h61;
                send_buf[5]  <= 8'h6C;
                send_buf[6]  <= 8'h3D;
                send_buf[7]  <= freq_digit[0];
                send_buf[8]  <= freq_digit[1];
                send_buf[9]  <= freq_digit[2];
                send_buf[10] <= freq_digit[3];
                send_buf[11] <= freq_digit[4];
                send_buf[12] <= 8'hFF;
                send_buf[13] <= 8'hFF;
                send_buf[14] <= 8'hFF;
                send_len     <= 4'd15;
                send_cnt     <= 4'd0;
                send_state   <= ST_TX;
            end

            ST_AMP_PREP: begin
                amp_bcd_temp <= amp_send;
                digit_idx    <= 3'd2;
                send_state   <= ST_AMP_DIG;
            end

            ST_AMP_DIG: begin
                amp_digit[digit_idx] <= amp_digit_val + 8'h30;
                amp_bcd_temp <= amp_bcd_next;
                if (digit_idx == 3'd0)
                    send_state <= ST_AMP_PACK;
                else
                    digit_idx <= digit_idx - 3'd1;
            end

            ST_AMP_PACK: begin
                send_buf[0]  <= 8'h6E;
                send_buf[1]  <= 8'h31;
                send_buf[2]  <= 8'h2E;
                send_buf[3]  <= 8'h76;
                send_buf[4]  <= 8'h61;
                send_buf[5]  <= 8'h6C;
                send_buf[6]  <= 8'h3D;
                send_buf[7]  <= amp_digit[0];
                send_buf[8]  <= amp_digit[1];
                send_buf[9]  <= amp_digit[2];
                send_buf[10] <= 8'hFF;
                send_buf[11] <= 8'hFF;
                send_buf[12] <= 8'hFF;
                send_len     <= 4'd13;
                send_cnt     <= 4'd0;
                send_state   <= ST_TX;
            end

            ST_TX: begin
                if (!tx_busy) begin
                    if (send_cnt < send_len) begin
                        tx_data <= send_buf[send_cnt];
                        tx_en   <= 1'b1;
                        send_cnt <= send_cnt + 4'd1;
                    end else if (send_len == 4'd15) begin
                        send_state <= ST_AMP_PREP;
                    end else begin
                        send_state <= ST_IDLE;
                    end
                end
            end

            default: send_state <= ST_IDLE;
        endcase
    end
end

assign freq_k  = freq_k_reg;
assign amp     = amp_reg;
assign uart_tx = uart_tx_reg;

endmodule
