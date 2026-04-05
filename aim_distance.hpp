#ifndef aim_distance_hpp
#define aim_distance_hpp

#define PID_CREATE(_kp, _ki, _kd, _low_pass, max_p, max_i, max_d) \
    {                                    \
        .kp = _kp,                       \
        .ki = _ki,                       \
        .kd = _kd,                       \
        .low_pass = _low_pass,           \
        .out_p = 0,                      \
        .out_i = 0,                      \
        .out_d = 0,                      \
        .p_max = max_p,                  \
        .i_max = max_i,                  \
        .d_max = max_d,                  \
    }


#endif /* _PID_H_ */
