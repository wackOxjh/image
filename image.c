#include "zf_common_headfile.h"
uint8 length_max = 0;
uint8 Stop_car_Flag = 0;
//int flag_ceshi = 0;
int ImageScanInterval;                         //鎵敓绔嚖鎷峰洿    閿熸枻鎷蜂竴閿熷彨鐨勮竟鏂ゆ嫹+-ImageScanInterval
int ImageScanInterval_Cross;                   //270閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍗侀敓琛楃鎷锋壂閿熺鍑ゆ嫹鍥�
uint8 Image_Use[LCDH][LCDW];          //閿熸彮璁规嫹鍥鹃敓鏂ゆ嫹
// uint8 Pixle[LCDH][LCDW];              //閿熸枻鎷烽敓鑺傝揪鎷烽敓鏂ゆ嫹閿熶茎璁规嫹鍊奸敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹
uint8 uPixle[uLCDH][uLCDW];                      //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷风ず閿熸枻鎷峰帇閿熸枻鎷蜂憨閿熻纰夋嫹閿熼叺纭锋嫹閿燂拷
uint8 UImage_Use[uLCDH][uLCDW];                  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷风ず閿熸枻鎷峰帇閿熸枻鎷峰箷鍙堕敓閰电》鎷烽敓锟�
static int Ysite = 0, Xsite = 0;                   //Y閿熸枻鎷烽敓鏂ゆ嫹=閿熸枻鎷�
static uint8* PicTemp;                             //閿熸枻鎷烽敓鑺ュ崟閿熸枻鎷峰浘閿熸枻鎷�
static int IntervalLow = 0, IntervalHigh = 0;      //閿熸枻鎷烽敓鏂ゆ嫹鍙╅敓缂搭煉鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
static int ytemp = 0;                              //閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
static int TFSite = 0, FTSite = 0;                 //閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
static float DetR = 0, DetL = 0;                   //閿熸枻鎷烽敓鍙唻鎷烽敓锟�
static int BottomBorderRight = 79,                 //59閿熸枻鎷烽敓鎻竟鏂ゆ嫹
BottomBorderLeft = 0,                              //59閿熸枻鎷烽敓鏂ゆ嫹鍛撻敓锟�
BottomCenter = 0;                                  //59閿熸枻鎷烽敓鍙鎷�
ImageDealDatatypedef ImageDeal[60];                //閿熸枻鎷峰綍閿熸枻鎷烽敓鍙鎷烽敓鏂ゆ嫹鎭�
ImageStatustypedef ImageStatus;                    //鍥鹃敓鏂ゆ嫹閿熼ズ顐嫹鐩撮敓鏂ゆ嫹閿燂拷
ImageStatustypedef ImageData;             ///////閿熸枻鎷疯閿熺潾鏀圭鎷峰浘閿熸枻鎷烽敓鏂ゆ嫹鍊奸敓鏂ゆ嫹閿熸枻鎷�
SystemDatatypdef SystemData;
ImageFlagtypedef ImageFlag;
uint8 Ring_Help_Flag = 0;                      //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰織
int Left_RingsFlag_Point1_Ysite, Left_RingsFlag_Point2_Ysite;   //閿熸枻鎷峰渾閿熸枻鎷烽敓鍙柇纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
int Right_RingsFlag_Point1_Ysite, Right_RingsFlag_Point2_Ysite; //閿熸枻鎷峰渾閿熸枻鎷烽敓鍙柇纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
int Point_Xsite,Point_Ysite;                   //閿熺Ц纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
int Repair_Point_Xsite,Repair_Point_Ysite;     //閿熸枻鎷烽敓绔鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
int forklenth;                                 //纭敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹浣嶉敓鏂ゆ嫹
int barnlenth;                                 //纭敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹浣嶉敓鏂ゆ嫹
int ramplenth;                                 //纭敓鏂ゆ嫹閿熼摪纰夋嫹浣嶉敓鏂ゆ嫹
uint16 exposure_time_self = 300;
float Weighting[10] = {0.96, 0.92, 0.88, 0.83, 0.77,0.71, 0.65, 0.59, 0.53, 0.47};//10閿熸枻鎷锋潈閿熸埅璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋ā閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎺ュ府鎷锋顒婃嫹閿熸枻鎷锋幊閿熸枻鎷烽敓鏂ゆ嫹閿熸暀顒婃嫹妞嶉敓鏂ゆ嫹閿熸枻鎷烽敓锟�
uint8 ExtenLFlag = 0;  //閿熻鍑ゆ嫹閿熸枻鎷烽敓鎺ョ鎷烽敓鏂ゆ嫹蹇�
uint8 ExtenRFlag = 0;  //閿熻鍑ゆ嫹閿熸枻鎷烽敓鎺ョ鎷烽敓鏂ゆ嫹蹇�
float ang_l;
int ycircle=0;
int xcircle=0;
int axcircle=0;
int aycircle=0;
int bxcircle=0;
int bycircle=0;
float K;
uint8 Half_Road_Wide[60] =                      //鐩撮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
{  1, 1, 1, 1, 2, 2, 3, 3, 4, 4,
        5, 5,6,6,7,8,8,9,9,10,
       11,11,11,12,13,13,14,15,15,16,
       16,17,18,18,19,19,20,20,21,22,
       22,23,23,24,25,25,25,26,27,27,
       28,28,29,30,30,30,31,32,32,33,
};

uint8 Half_Bend_Wide[60] =                      //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
{   33,33,33,33,33,33,33,33,33,33,
    33,33,32,32,30,30,29,29,28,27,
    28,27,27,26,26,25,25,24,24,23,
    22,21,21,22,22,22,23,24,24,24,
    25,25,25,26,26,26,27,27,28,28,
    28,29,29,30,30,31,31,32,32,33,
};


uint8 buxianwide[60]={6,7,8,9,10,11,12,13,14,15,
                      16,17,18,19,20,21,22,23,24,25,
                      26,27,28,29,30,31,32,33,34,35,
                      36,37,38,39,40,41,42,43,44,45,
                      46,47,48,49,50,51,52,53,54,55,
                      56,57,58,59,60,61,62,63,64,65};

int adczongzhi;
int tuoluoyijifen;//閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�

int Limit(int num, int numH, int numL) {
  if (num > numH)
    num = numH;
  if (num < numL)
    num = numL;
  return num;
}
//void camera_display(void) {
//  if (mt9v03x_finish_flag == 1) {  //閿熸枻鎷风ず閿熸枻鎷烽敓鏂ゆ嫹 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//    if (SystemData.GO_OK || SystemData.CameraOK == 1 ||
//        SystemData.OldCameraOK == 1)
//         ImageProcess(); //5-6ms
//
//    static int cnt = 0;
//    ++cnt;
//    cnt %= 2;
//    if (!cnt) {
//      if (SystemData.CameraOK == 1)  //閿熸枻鎷烽敓鐨嗙鎷锋椂閿熸枻鎷烽敓锟�  閿熸澃纰夋嫹鏃堕敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//        ips114_displayimage01(uPixle[0], uLCDW, uLCDH);
//      else if (SystemData.OldCameraOK == 1)
//        ips114_displayimage032(UImage_Use[0], uLCDW, uLCDH);
//    }
//  }
//}
/*****************鐩撮敓鏂ゆ嫹閿熷彨璁规嫹******************/
float Straight_Judge(uint8 dir, uint8 start, uint8 end)     //閿熸枻鎷烽敓鎴枻鎷烽敓鍙槄鎷烽敓锟�1閿熸枻鎷蜂负鐩撮敓鏂ゆ嫹
{
    int i;
    float S = 0, Sum = 0, Err = 0, k = 0;
    switch (dir)
    {
    case 1:k = (float)(ImageDeal[start].LeftBorder - ImageDeal[end].LeftBorder) / (start - end);
        for (i = 0; i < end - start; i++)
        {
            Err = (ImageDeal[start].LeftBorder + k * i - ImageDeal[i + start].LeftBorder) * (ImageDeal[start].LeftBorder + k * i - ImageDeal[i + start].LeftBorder);
            Sum += Err;
        }
        S = Sum / (end - start);
        break;
    case 2:k = (float)(ImageDeal[start].RightBorder - ImageDeal[end].RightBorder) / (start - end);
        for (i = 0; i < end - start; i++)
        {
            Err = (ImageDeal[start].RightBorder + k * i - ImageDeal[i + start].RightBorder) * (ImageDeal[start].RightBorder + k * i - ImageDeal[i + start].RightBorder);
            Sum += Err;
        }
        S = Sum / (end - start);
        break;
    }
    return S;
}


float Straight_Judge_two(uint8 flag)//閿熸枻鎷烽敓鎴枻鎷烽敓鍙槄鎷烽敓锟�1閿熸枻鎷蜂负鐩撮敓鏂ゆ嫹
{
    float out=0;
    int X_temp[12],Y_temp[12],i=0,Point=1,j=1;
    float K_temp,K_other[12];
    if(flag==1)//閿熸枻鎷烽敓鏂ゆ嫹閿熺嫛鏂ゆ嫹閿熷彨鎲嬫嫹濮嬮敓鏂ゆ嫹閿燂拷
    {
        for(i=ImageStatus.OFFLine+5;i<30;i++)
        {
            if((ImageDeal[i].IsLeftFind=='T')&&(ImageDeal[i].LeftBorder>2))
            {
                X_temp[0]=ImageDeal[i].LeftBorder;
                Y_temp[0]=i;
                break;
            }
            if(i>=19)return 1;
        }
        i+=5;
        for(;i<50;i=i+5)
        {
            if((ImageDeal[i].IsLeftFind=='T')&&(ImageDeal[i].LeftBorder>2))
            {
                Point++;
                X_temp[j]=ImageDeal[i].LeftBorder;
                Y_temp[j]=i;
                j++;
            }
        }
        if(Point<5)return 1;
        else
        {
            K_temp=(float)(X_temp[0]-X_temp[Point-1])/(float)(Y_temp[Point-1]-Y_temp[0]);
            for(i=1;i<Point-1;i++)
            {
                K_other[i]=(float)(X_temp[0]-X_temp[i])/(float)(Y_temp[i]-Y_temp[0]);
                out+=(K_temp-K_other[i])*(K_temp-K_other[i]);
            }
        }
        if(K_temp<0)return 1;
    }
    else//閿熸彮鎲嬫嫹閿熸枻鎷峰钩閿熸枻鎷锋枩閿熺粸纭锋嫹閿熸枻鎷�
    {
        for(i=ImageStatus.OFFLine+5;i<30;i++)
        {
            if((ImageDeal[i].IsRightFind=='T')&&(ImageDeal[i].RightBorder<77))
            {
                X_temp[0]=ImageDeal[i].RightBorder;
                Y_temp[0]=i;
                break;
            }
            if(i>=19)return 1;
        }
        i+=5;
        for(;i<50;i=i+5)
        {
            if((ImageDeal[i].IsRightFind=='T')&&(ImageDeal[i].RightBorder<77))
            {
                Point++;
                X_temp[j]=ImageDeal[i].RightBorder;
                Y_temp[j]=i;
                j++;
            }
        }
        if(Point<5)return 1;
        else
        {
            K_temp=(float)(X_temp[0]-X_temp[Point-1])/(float)(Y_temp[0]-Y_temp[Point-1]);
            for(i=1;i<Point-1;i++)
            {
                K_other[i]=(float)(X_temp[0]-X_temp[i])/(float)(Y_temp[0]-Y_temp[i]);
                out+=(K_temp-K_other[i])*(K_temp-K_other[i]);
            }
        }
        if(K_temp<0)return 1;
    }
    return out;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      閿熸枻鎷峰皬閿熸枻鎷烽敓鍓垮嚖鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
//  @param      start    閿熸枻鎷峰閿熸枻鎷�
//  @param      num      閿熸枻鎷烽敓鎹烽潻鎷烽敓鏂ゆ嫹
//  @return     void
//  @since      v1.0
//  Sample usage:  Fit1(119,20);
//-------------------------------------------------------------------------------------------------------------------
void Fit1(int start,int num)
{
    float sum_x = 0.0;
    float sum_y = 0.0;
    float sum_x2 = 0.0;
    float sum_xy = 0.0;
    float a,b;
    float y = 0;

    for (int i = 0; i < num; ++i)
    {
        sum_x += y++;
        sum_y += ImageDeal[start-num+i].Center;
        sum_x2 += (y-1) * (y-1);
        sum_xy += (y-1) * ImageDeal[start-num+i].Center;
    }

    sum_x /= num;
    sum_y /= num;
    sum_x2 /= num;
    sum_xy /= num;

    a = (sum_xy - sum_x * sum_y) / (sum_x2 - sum_x * sum_x);
    b = (sum_x2 * sum_y - sum_x * sum_xy) / (sum_x2 - sum_x * sum_x);
    for(int i = 0;i<num;i++)
    {
     ImageDeal[start-num+i].Center = a*i+b;
    }
}

float Get_angle(float Ax, float Ay, float Bx, float By, float Cx, float Cy)
{
    float BA = 0.00;//閿熸枻鎷烽敓鏂ゆ嫹BA閿熸枻鎷锋ā
    float BC = 0.00;
    float SBA_BC = 0.00;//閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熻锟�
    float angle = 0.00;

    BA = sqrt((Ax-Bx)*(Ax-Bx)+(Ay-By)*(Ay-By));
    BC = sqrt((Cx-Bx)*(Cx-Bx)+(Cy-By)*(Cy-By));

    SBA_BC = (Ax-Bx)*(Cx-Bx)+(Ay-By)*(Cy-By);

    angle =  acos(SBA_BC*1.00/(BA*BC));

    return angle*57.3;
}

float Fit1_k(int start,int num)
{
    float sum_x = 0.0;
    float sum_y = 0.0;
    float sum_x2 = 0.0;
    float sum_xy = 0.0;
    float a,b;
    float y = 0;
    uint16 middle_NO[60] = {0};

    for (int i = 0; i < num; ++i)
    {
        sum_x += y++;
        sum_y += ImageDeal[start-num+i].Center;
        sum_x2 += (y-1) * (y-1);
        sum_xy += (y-1) * ImageDeal[start-num+i].Center;
    }

    sum_x /= num;
    sum_y /= num;
    sum_x2 /= num;
    sum_xy /= num;

    a = (sum_xy - sum_x * sum_y) / (sum_x2 - sum_x * sum_x);
    b = (sum_x2 * sum_y - sum_x * sum_xy) / (sum_x2 - sum_x * sum_x);
    for(int i = 0;i<num;i++)
    {
        middle_NO[start-num+i] = a*i+b;
    }

    float Y = 59-ImageStatus.OFFLine+10-1 - 59-ImageStatus.OFFLine+1;                          //閿熸枻鎷穀閿熺粨闀块敓鏂ゆ嫹
    float X = middle_NO[59-ImageStatus.OFFLine+10-1] - middle_NO[59-ImageStatus.OFFLine+1];    //閿熸枻鎷稾閿熺粨闀块敓鏂ゆ嫹(閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�)
    float k = 1.00*(X/Y);                             //閿熸枻鎷锋枩閿熸枻鎷�(閿熸枻鎷穣閿熸枻鎷蜂负閿熸枻鎷�)
    if(k<0)  k = k*-1;
    return k;
}

float Mh = MT9V03X_H;
float Lh = LCDH;
float Mw = MT9V03X_W;
float Lw = LCDW;

void compressimage() {
  int i, j, row, line;
  const float div_h = Mh / Lh, div_w = Mw / Lw;

  for (i = 0; i < LCDH; i++) {
    row = i * div_h + 0.5;
    for (j = 0; j < LCDW; j++) {
      line = j * div_w + 0.5;
      Image_Use[i][j] =mt9v03x_image[row][line];
    }
  }
  mt9v03x_finish_flag = 0;  //浣块敓鏂ゆ嫹閿熸枻鎷蜂竴甯MA閿熸枻鎷烽敓鏂ゆ嫹閿熼叺纭锋嫹閿熼叺纭锋嫹閿燂拷  閿熸枻鎷烽敓鐨嗗尅鎷峰閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷蜂竴甯�
}


int HD_thre;  //閿熸枻鎷锋椂閿熸璇ф嫹閿熸枻鎷烽敓锟�
//閿熸枻鎷峰€奸敓鏂ゆ嫹
void Get01change() {
  uint8 thre;
  uint8 i, j;
  for (i = 0; i < LCDH; i++) {
    for (j = 0; j < LCDW; j++) {
      if (j <= 15)
        thre = ImageStatus.Threshold_static - 10;
      else if ((j > 70 && j <= 75))
        thre = ImageStatus.Threshold_static - 15;
      else if (j >= 65)
        thre = ImageStatus.Threshold_static - 15;
      else
        thre = ImageStatus.Threshold_static;

      if (Image_Use[i][j] >
          (thre))  //閿熸枻鎷峰€艰秺閿熸枻鎷烽敓鏂ゆ嫹绀洪敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹瓒婇敓娲侊紝閿熸枻鎷锋祬閿熸枻鎷峰浘閿熸枻鎷蜂篃閿熸枻鎷烽敓鏂ゆ嫹绀洪敓鏂ゆ嫹閿熸枻鎷�
        Pixle[i][j] = 1;  //閿熸枻鎷�
      else
        Pixle[i][j] = 0;  //閿熸枻鎷�
    }
  }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      閿熻剼浼欐嫹閿熶茎杈炬嫹閿燂拷
//  @param      image  鍥鹃敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//  @param      clo    閿熸枻鎷�
//  @param      row    閿熸枻鎷�
//  @param      pixel_threshold 閿熸枻鎷峰€奸敓鏂ゆ嫹閿熸枻鎷�
//  @return     uint8
//  @since      2021.6.23
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 Threshold_deal(uint8* image,
                     uint16 col,
                     uint16 row,
                     uint32 pixel_threshold) {
#define GrayScale 256
  uint16 width = col;
  uint16 height = row;
  int pixelCount[GrayScale];
  float pixelPro[GrayScale];
  int i, j, pixelSum = width * height;
  uint8 threshold = 0;
  uint8* data = image;  //鎸囬敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎹风鎷锋寚閿熸枻鎷�
  for (i = 0; i < GrayScale; i++) {
    pixelCount[i] = 0;
    pixelPro[i] = 0;
  }

  uint32 gray_sum = 0;
  //缁熼敓鐙＄伆搴︾》鎷烽敓鏂ゆ嫹姣忛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰浘閿熸枻鎷烽敓鍙殑闈╂嫹閿熸枻鎷�
  for (i = 0; i < height; i += 1) {
    for (j = 0; j < width; j += 1) {
      // if((sun_mode&&data[i*width+j]<pixel_threshold)||(!sun_mode))
      //{
      pixelCount[(
          int)data[i * width + j]]++;  //閿熸枻鎷烽敓鏂ゆ嫹鍓嶉敓渚ョ鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓琛楃鎷烽敓杞款亷鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓閾版唻鎷�
      gray_sum += (int)data[i * width + j];  //閿熸彮璁规嫹鍊奸敓鏉扮尨鎷�
      //}
    }
  }

  //閿熸枻鎷烽敓鏂ゆ嫹姣忛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍊奸敓渚ョ鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹閿熷彨鐨勬唻鎷烽敓鏂ゆ嫹
  for (i = 0; i < GrayScale; i++) {
    pixelPro[i] = (float)pixelCount[i] / pixelSum;
  }


  //閿熸枻鎷烽敓鏂ゆ嫹閿熸彮搴︾》鎷穂0,255]
  float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
  w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
  for (j = 0; j < pixel_threshold; j++) {
    w0 +=
        pixelPro[j];  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹姣忛敓鏂ゆ嫹閿熸彮璁规嫹鍊奸敓鏂ゆ嫹閿熸枻鎷烽敓鎴鎷烽敓鏂ゆ嫹鍗犻敓鏂ゆ嫹閿熸枻鎷蜂箣閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻鐨勬唻鎷烽敓鏂ゆ嫹
    u0tmp += j * pixelPro[j];  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹 姣忛敓鏂ゆ嫹閿熸彮璁规嫹鍊奸敓渚ョ鎷疯皨閿熸枻鎷烽敓锟� *閿熸彮璁规嫹鍊�

    w1 = 1 - w0;
    u1tmp = gray_sum / pixelSum - u0tmp;

    u0 = u0tmp / w0;    //閿熸枻鎷烽敓鏂ゆ嫹骞抽敓鏂ゆ嫹閿熸彮璁规嫹
    u1 = u1tmp / w1;    //鍓嶉敓鏂ゆ嫹骞抽敓鏂ゆ嫹閿熸彮璁规嫹
    u = u0tmp + u1tmp;  //鍏ㄩ敓鏂ゆ嫹骞抽敓鏂ゆ嫹閿熸彮璁规嫹
    deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
    if (deltaTmp > deltaMax) {
      deltaMax = deltaTmp;
      threshold = j;
    }
    if (deltaTmp < deltaMax) break;
  }
  return threshold;
}

void Get01change_dajin() {
  ImageStatus.Threshold = Threshold_deal(Image_Use[0], LCDW, LCDH, ImageStatus.Threshold_detach);
  if (ImageStatus.Threshold < ImageStatus.Threshold_static)
    ImageStatus.Threshold = ImageStatus.Threshold_static;
  uint8 i, j = 0;
  uint8 thre;
  for (i = 0; i < LCDH; i++) {
    for (j = 0; j < LCDW; j++) {
      if (j <= 15)
        thre = ImageStatus.Threshold - 5;
      else if ((j > 70 && j <= 75))
        thre = ImageStatus.Threshold - 5;
      else if (j >= 65)
        thre = ImageStatus.Threshold - 5;
      else
        thre = ImageStatus.Threshold;

      if (Image_Use[i][j] >(thre))         //閿熸枻鎷峰€艰秺閿熸枻鎷烽敓鏂ゆ嫹绀洪敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹瓒婇敓娲侊紝閿熸枻鎷锋祬閿熸枻鎷峰浘閿熸枻鎷蜂篃閿熸枻鎷烽敓鏂ゆ嫹绀洪敓鏂ゆ嫹閿熸枻鎷�
        Pixle[i][j] = 1;  //閿熸枻鎷�
      else
        Pixle[i][j] = 0;  //閿熸枻鎷�
    }
  }
}


//閿熸枻鎷烽敓鏂ゆ嫹閿熷壙璇ф嫹
void Pixle_Filter() {
  int nr;  //閿熸枻鎷�
  int nc;  //閿熸枻鎷�

  for (nr = 10; nr < 40; nr++) {
    for (nc = 10; nc < 70; nc = nc + 1) {
      if ((Pixle[nr][nc] == 0) && (Pixle[nr - 1][nc] + Pixle[nr + 1][nc] +
                                       Pixle[nr][nc + 1] + Pixle[nr][nc - 1] >=
                                   3)) {
        Pixle[nr][nc] = 1;
      }
      //      else
      //      if((Pixle[nr][nc]==1)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]<2))
      //      {
      //        Pixle[nr][nc]=0;
      //      }
    }
  }
}

// 01閿熸枻鎷峰帇鍥鹃敓鏂ゆ嫹
//void uncompressimage() {
//  int i = 0, j = 0, row = 0, line = 0;
//  int div_h = uLCDH / LCDH;
//  int div_w = uLCDW / LCDW;
//  for (i = 0; i < uLCDH; i++) {
//    for (j = 0; j < uLCDW; j++) {
//      row = (int)(i / div_h);
//      line = (int)(j / div_w);
//      uPixle[i][j] = Pixle[row][line];
//    }
//  }
//}
////閿熸彮搴︽枻鎷峰帇鍥鹃敓鏂ゆ嫹
//void uncompressimageHD() {
//  int i = 0, j = 0, row = 0, line = 0;
//  int div_h = uLCDH / LCDH;
//  int div_w = uLCDW / LCDW;
//  for (i = 0; i < uLCDH; i++) {
//    for (j = 0; j < uLCDW; j++) {
//      row = (int)(i / div_h);
//      line = (int)(j / div_w);
//      UImage_Use[i][j] = Image_Use[row][line];
//    }
//  }
//}
//


void GetJumpPointFromDet(uint8* p,uint8 type,int L,int H,JumpPointtypedef* Q)  //閿熸枻鎷蜂竴閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹瑕侀敓鏂ゆ嫹閿熸彮纰夋嫹閿熸枻鎷烽敓浠嬶紙80閿熸枻鎷烽敓濮愶級
                                                                               //閿熻妭璁规嫹閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹鍛嬮敓鏂ゆ嫹閿熺即顭掓嫹鍐堕敓鏂ゆ嫹閿燂拷
{                                                                              //閿熸枻鎷烽敓鏂ゆ嫹閿熻鍖℃嫹濮嬮敓閰垫枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
  int i = 0;
  if (type == 'L')                              //鎵敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
  {
    for (i = H; i >= L; i--) {
      if (*(p + i) == 1 && *(p + i - 1) != 1)   //閿熺即榛戞唻鎷烽敓锟�
      {
        Q->point = i;                           //閿熸枻鎷峰綍閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
        Q->type = 'T';                          //閿熸枻鎷风‘閿熸枻鎷烽敓鏂ゆ嫹
        break;
      } else if (i == (L + 1))                  //閿熸枻鎷烽敓鏂ゆ嫹鎵敓鏂ゆ嫹閿熸枻鎷烽敓鎻浼欐嫹涓氶敓锟�
      {
        if (*(p + (L + H) / 2) != 0)            //閿熸枻鎷烽敓鏂ゆ嫹灞戦敓鏂ゆ嫹鍓嶆閿燂拷
        {
          Q->point = (L + H) / 2;               //閿熸枻鎷蜂负閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹姊伴敓锟�
          Q->type = 'W';                        //閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨纭锋嫹涓洪敓闃讹綇鎷烽敓鏂ゆ嫹涓烘病閿熷彨鎲嬫嫹
          break;
        } else                                  //閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨纭锋嫹涓洪敓鏂ゆ嫹
        {
          Q->point = H;                         //閿熸枻鎷烽敓鏂ゆ嫹灞戦敓鏂ゆ嫹鍛涜瘶閿燂拷
          Q->type = 'H';                        //閿熸枻鎷烽敓鏂ゆ嫹閿熻鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹鍊奸敓鏂ゆ嫹閿熸枻鎷蜂负閿熻杈炬嫹閿熸枻鎷烽敓鏂ゆ嫹
          break;
        }
      }
    }
  } else if (type == 'R')                       //鎵敓鏂ゆ嫹閿熸彮鎲嬫嫹閿熸枻鎷�
  {
    for (i = L; i <= H; i++)                    //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鎵�
    {
      if (*(p + i) == 1 && *(p + i + 1) != 1)   //閿熸枻鎷烽敓缂撮粦纰夋嫹閿熼樁纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹
      {
        Q->point = i;                           //閿熸枻鎷峰綍
        Q->type = 'T';
        break;
      } else if (i == (H - 1))                  //閿熸枻鎷烽敓鏂ゆ嫹鎵敓鏂ゆ嫹閿熸枻鎷烽敓鎻浼欐嫹涓氶敓锟�
      {
        if (*(p + (L + H) / 2) != 0)            //閿熸枻鎷烽敓鏂ゆ嫹灞戦敓鏂ゆ嫹鍓嶆閿燂拷
        {
          Q->point = (L + H) / 2;               //閿熸彮鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨纰夋嫹
          Q->type = 'W';
          break;
        } else                                  //閿熸枻鎷烽敓鏂ゆ嫹姊伴敓鏂ゆ嫹鍛涜瘶閿燂拷
        {
          Q->point = L;                         //閿熸枻鎷烽敓鏂ゆ嫹閿熻鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹鍊�
          Q->type = 'H';
          break;
        }
      }
    }
  }
}





static uint8 DrawLinesFirst(void) {
  PicTemp = Pixle[59];                                     //鍘熼敓鏂ゆ嫹59  閿熶茎绛规嫹閿熸枻鎷�57
  if (*(PicTemp + ImageSensorMid) == 0)                 //閿熸枻鎷烽敓鏂ゆ嫹濡嗛敓閰电》鎷烽敓鏂ゆ嫹姊伴敓杞款亷鎷峰啟閿熸枻鎷锋枑锝忔嫹閿熸枻鎷�
  {
    for (Xsite = 0; Xsite < ImageSensorMid; Xsite++)    //閿熸枻鎷烽敓鏂ゆ嫹閿熸彮鎲嬫嫹閿熸枻鎷�
    {
      if (*(PicTemp + ImageSensorMid - Xsite) != 0)     //涓€閿熸枻鎷烽敓鎻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鏈ㄩ敓鏂ゆ嫹鑰勵剨鎷烽敓绲檙eak
        break;                                          //閿熸枻鎷烽敓鎻》鎷峰綍Xsite
      if (*(PicTemp + ImageSensorMid + Xsite) != 0)
        break;
    }

    if (*(PicTemp + ImageSensorMid - Xsite) != 0)       //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓绔殑浼欐嫹
    {
      BottomBorderRight = ImageSensorMid - Xsite + 1;   // 59閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
      for (Xsite = BottomBorderRight; Xsite > 0; Xsite--)  //閿熸枻鎷峰閿熸枻鎷�59閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
      {
        if (*(PicTemp + Xsite) == 0 &&
            *(PicTemp + Xsite - 1) == 0)                //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻妭鐐癸紝閿熷壙璇ф嫹
        {
          BottomBorderLeft = Xsite;                     //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷蜂笟閿燂拷
          break;
        } else if (Xsite == 1) {
          BottomBorderLeft = 0;                         //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯€嶉敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺锝忔嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓杞款亷鎷烽敓锟�0
          break;
        }
      }
    } else if (*(PicTemp + ImageSensorMid + Xsite) != 0)  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰喍鍙╁箷閿燂拷
    {
      BottomBorderLeft = ImageSensorMid + Xsite - 1;    // 59閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
      for (Xsite = BottomBorderLeft; Xsite < 79; Xsite++)  //閿熸枻鎷峰閿熸枻鎷�59閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
      {
        if (  *(PicTemp + Xsite) == 0
            &&*(PicTemp + Xsite + 1) == 0)              //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻妭鐐癸紝閿熷壙璇ф嫹
        {
          BottomBorderRight = Xsite;                    //閿熸彮鎲嬫嫹閿熸枻鎷烽敓鎻鎷�
          break;
        } else if (Xsite == 78) {
          BottomBorderRight = 79;                       //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯€嶉敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰喍閿熸枻鎷锋捀閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹涓洪敓鏂ゆ嫹79
          break;
        }
      }
    }
  }
  else                                                //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋閿熸枻鎷峰墠妞庢ā閿熸枻鎷峰唹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
  {
    for (Xsite = 79; Xsite >ImageSensorMid; Xsite--)   //涓€閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰喍閿熸枻鎷烽敓锟�
    {
      if (  *(PicTemp + Xsite) == 1
          &&*(PicTemp + Xsite - 1) == 1)                //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻妭鐐癸紝閿熷壙璇ф嫹     //閿熸枻鎷烽敓鏂ゆ嫹閿熼樁纰夋嫹
      {
        BottomBorderRight = Xsite;                      //閿熸彮纰夋嫹閿熼叺纭锋嫹褰�
        break;
      } else if (Xsite == 40) {
        BottomBorderRight = 39;                         //閿熸彮璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹涓�79
        break;
      }
    }
    for (Xsite = 0; Xsite < ImageSensorMid; Xsite++)    //涓€閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    {
      if (  *(PicTemp + Xsite) == 1
          &&*(PicTemp + Xsite + 1) == 1)                //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻妭鐐癸紝閿熷壙璇ф嫹
      {
        BottomBorderLeft = Xsite;                       //閿熸彮纰夋嫹閿熼叺纭锋嫹褰�
        break;
      } else if (Xsite == 38) {
        BottomBorderLeft = 39;                           //閿熸彮璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹涓�0
        break;
      }
    }
  }
  BottomCenter =(BottomBorderLeft + BottomBorderRight) / 2;   // 59閿熸枻鎷烽敓鍙鎷风洿閿熸枻鎷峰彇骞抽敓鏂ゆ嫹
  ImageDeal[59].LeftBorder = BottomBorderLeft;                //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓閾板浼欐嫹閿熸枻鎷烽敓杈冾澁鎷烽敓鏂ゆ嫹閿熸彮浼欐嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸彮浼欐嫹閿熸枻鎷烽敓鏂ゆ嫹
  ImageDeal[59].RightBorder = BottomBorderRight;
  ImageDeal[59].Center = BottomCenter;                        //纭敓鏂ゆ嫹閿熸枻鎷峰閿燂拷
  ImageDeal[59].Wide = BottomBorderRight - BottomBorderLeft;  //閿熻姤鍌ㄩ敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鎭�
  ImageDeal[59].IsLeftFind = 'T';
  ImageDeal[59].IsRightFind = 'T';
  for (Ysite = 58; Ysite > 54; Ysite--)                       //閿熸枻鎷烽敓鍙》鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熼樁鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹
  {
    PicTemp = Pixle[Ysite];
    for (Xsite = 79; Xsite > ImageDeal[Ysite + 1].Center;Xsite--)                                             //閿熸枻鎷峰墠閿熸枻鎷蜂竴閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
    {
      if (*(PicTemp + Xsite) == 1 && *(PicTemp + Xsite - 1) == 1) {
        ImageDeal[Ysite].RightBorder = Xsite;
        break;
      } else if (Xsite == (ImageDeal[Ysite + 1].Center+1)) {
        ImageDeal[Ysite].RightBorder = ImageDeal[Ysite + 1].Center;
        break;
      }
    }
    for (Xsite = 0; Xsite < ImageDeal[Ysite + 1].Center;Xsite++)                                             //閿熸枻鎷峰墠閿熸枻鎷蜂竴閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
    {
      if (*(PicTemp + Xsite) == 1 && *(PicTemp + Xsite + 1) == 1) {
        ImageDeal[Ysite].LeftBorder = Xsite;
        break;
      } else if (Xsite == (ImageDeal[Ysite + 1].Center-1)) {
        ImageDeal[Ysite].LeftBorder = ImageDeal[Ysite + 1].Center;
        break;
      }
    }
    ImageDeal[Ysite].IsLeftFind = 'T';                        //閿熸枻鎷蜂簺閿熸枻鎷锋伅閿熻姤鍌ㄩ敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    ImageDeal[Ysite].IsRightFind = 'T';
    ImageDeal[Ysite].Center =
        (ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) /2; //閿熻姤鍌ㄩ敓鍙鎷�
    ImageDeal[Ysite].Wide =
        ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;      //閿熻姤鍌ㄩ敓鏂ゆ嫹閿熸枻鎷�
  }
  return 'T';
}                                                             //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎻亷鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓楗鸿鎷烽敓鏂ゆ嫹閿熸澃纰夋嫹閿熸枻鎷烽敓鑴氾綇鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熻妭甯嫹瑁呴敓鏂ゆ嫹鏃堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓閰靛嚖鎷烽敓鏂ゆ嫹鍜忛敓锟�

/*閿熸枻鎷烽敓鏂ゆ嫹杩介敓鏂ゆ嫹閿熸枻鎷风鐜敓楗侯偓鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�*/
static void DrawLinesProcess(void)  //////閿熸枻鎷烽敓鐭潻鎷烽敓鏂ゆ嫹
{
  uint8 L_Found_T = 'F';  //纭敓鏂ゆ嫹閿熺潾鎲嬫嫹鏂滈敓缁炵殑浼欐嫹鍑嗛敓鍙唻鎷烽敓鏂ゆ嫹閿熻鍑ゆ嫹閿熸彮纰夋嫹閿熶茎鎲嬫嫹蹇�
  uint8 Get_L_line = 'F';  //閿熸彮纰夋嫹閿熸枻鎷蜂竴甯у浘閿熸枻鎷峰箷閿熼樁纭锋嫹閿熷彨鎲嬫嫹閿燂拷
  uint8 R_Found_T = 'F';  //纭敓鏂ゆ嫹閿熺潾鎲嬫嫹鏂滈敓缁炵殑浼欐嫹鍑嗛敓鍙唻鎷烽敓鏂ゆ嫹閿熻鍑ゆ嫹閿熸彮纰夋嫹閿熶茎鎲嬫嫹蹇�
  uint8 Get_R_line = 'F';  //閿熸彮纰夋嫹閿熸枻鎷蜂竴甯у浘閿熸枻鎷峰箷閿熼樁纭锋嫹閿熷彨鎲嬫嫹閿燂拷
  float D_L = 0;           //閿熸帴绛规嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙唻鎷烽敓锟�
  float D_R = 0;           //閿熸帴绛规嫹閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹鏂滈敓鏂ゆ嫹
  int ytemp_W_L;           //閿熸枻鎷蜂綇閿熼樁杈炬嫹閿熻涓㈡唻鎷烽敓鏂ゆ嫹
  int ytemp_W_R;           //閿熸枻鎷蜂綇閿熼樁杈炬嫹閿熸彮璁规嫹閿熸枻鎷烽敓鏂ゆ嫹
  ExtenRFlag = 0;          //閿熸枻鎷峰織浣嶉敓鏂ゆ嫹0
  ExtenLFlag = 0;
   ImageStatus.Left_Line = 0;
   ImageStatus.WhiteLine = 0;
   ImageStatus.Right_Line = 0;
  for (Ysite = 54 ; Ysite > ImageStatus.OFFLine; Ysite--)            //鍓�5閿熷彨杈炬嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷壙锝忔嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷55閿熷彨纰夋嫹閿熸枻鎷烽敓鍊熷畾閿熶茎璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹OFFLine閿熸枻鎷�
  {                        //澶繙閿熸枻鎷峰浘閿熸枻鎷烽敓楗鸿鎷烽敓鏂ゆ嫹OFFLine閿熺殕鐚存嫹鐗熼敓鏂ゆ嫹閿熸枻鎷烽敓锟�
    PicTemp = Pixle[Ysite];
    JumpPointtypedef JumpPoint[2];                                          // 0閿熸枻鎷�1閿熸枻鎷�
    if (ImageStatus.Road_type != Cross_ture
           /* &&SystemData.SpeedData.Length*OX>500*/) {
      IntervalLow =ImageDeal[Ysite + 1].RightBorder -ImageScanInterval;             //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹-Interval閿熶茎鐐瑰紑濮嬮敓鏂ゆ嫹纭敓鏂ゆ嫹鎵敓鍊熷紑濮嬮敓濮愶級
      IntervalHigh =ImageDeal[Ysite + 1].RightBorder + ImageScanInterval;           //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹+Interval閿熶茎纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熼ズ鍑ゆ嫹閿熺即顭掓嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷锛�
    } else {
      IntervalLow =ImageDeal[Ysite + 1].RightBorder -ImageScanInterval_Cross;       //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹-Interval_Cross閿熶茎鐐瑰紑濮嬮敓鏂ゆ嫹纭敓鏂ゆ嫹鎵敓鍊熷紑濮嬮敓濮愶級
      IntervalHigh = ImageDeal[Ysite + 1].RightBorder + ImageScanInterval_Cross;    //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹+Interval_Cross閿熶茎鐐瑰紑濮嬮敓鏂ゆ嫹纭敓鏂ゆ嫹鎵敓鍊熷紑濮嬮敓濮愶級
    }

    LimitL(IntervalLow);   //纭敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿熸垝骞堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    LimitH(IntervalHigh);  //纭敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿熸垝骞堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    GetJumpPointFromDet(PicTemp, 'R', IntervalLow, IntervalHigh,&JumpPoint[1]);     //鎵敓鎻唻鎷烽敓鏂ゆ嫹

    IntervalLow =ImageDeal[Ysite + 1].LeftBorder -ImageScanInterval;                //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�-5閿熶茎鐐瑰紑濮嬮敓鏂ゆ嫹纭敓鏂ゆ嫹鎵敓鍊熷紑濮嬮敓濮愶級
    IntervalHigh =ImageDeal[Ysite + 1].LeftBorder +ImageScanInterval;               //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�+5閿熶茎纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熼ズ鍑ゆ嫹閿熺即顭掓嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷锛�

    LimitL(IntervalLow);   //纭敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿熸垝骞堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    LimitH(IntervalHigh);  //纭敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿熸垝骞堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    GetJumpPointFromDet(PicTemp, 'L', IntervalLow, IntervalHigh,&JumpPoint[0]);

    if (JumpPoint[0].type =='W')                                                    //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓绔鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸垝锛岄敓鏂ゆ嫹閿熸枻鎷�10閿熸枻鎷烽敓濮愰兘閿熻鐧界鎷�
    {
      ImageDeal[Ysite].LeftBorder =ImageDeal[Ysite + 1].LeftBorder;                 //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸彮浼欐嫹姊伴敓鏂ゆ嫹閿熻锟�
    } else                                                                          //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
    {
      ImageDeal[Ysite].LeftBorder = JumpPoint[0].point;                             //閿熸枻鎷峰綍閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    }

    if (JumpPoint[1].type == 'W')                                                   //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍐堕敓鏂ゆ嫹鍗熼敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
    {
      ImageDeal[Ysite].RightBorder =ImageDeal[Ysite + 1].RightBorder;               //閿熸枻鎷烽敓鏂ゆ嫹閿熸彮鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷蜂竴閿熷彨纰夋嫹閿熸枻鎷峰€�
    } else                                                                          //閿熸彮鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    {
      ImageDeal[Ysite].RightBorder = JumpPoint[1].point;                            //閿熸枻鎷峰綍閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    }

    ImageDeal[Ysite].IsLeftFind =JumpPoint[0].type;                                 //閿熸枻鎷峰綍閿熸枻鎷烽敓鏂ゆ嫹閿熻鍑ゆ嫹閿熸彮纰夋嫹閿熸枻鎷烽敓绔綇鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
    ImageDeal[Ysite].IsRightFind = JumpPoint[1].type;

    //閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熸枻鎷蜂簺閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯皨閿熺殕锟�
    if (( ImageDeal[Ysite].IsLeftFind == 'H'
         ||ImageDeal[Ysite].IsRightFind == 'H')) {
      if (ImageDeal[Ysite].IsLeftFind == 'H')                                   //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓绔揪鎷烽敓鏂ゆ嫹閿熸枻鎷�
        for (Xsite = (ImageDeal[Ysite].LeftBorder + 1);
             Xsite <= (ImageDeal[Ysite].RightBorder - 1);
             Xsite++)                                                           //閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹涔嬮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鎵敓鏂ゆ嫹
        {
          if ((*(PicTemp + Xsite) == 0) && (*(PicTemp + Xsite + 1) != 0)) {
            ImageDeal[Ysite].LeftBorder =Xsite;                                 //閿熸枻鎷烽敓鏂ゆ嫹閿熸彮浼欐嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺纰夋嫹閿熸彮鎲嬫嫹閿熷彨榛戝府鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹涓洪敓鏂ゆ嫹閿熺殕鎲嬫嫹閿熸枻鎷风洿閿熸枻鎷峰彇閿熸枻鎷�
            ImageDeal[Ysite].IsLeftFind = 'T';
            break;
          } else if (*(PicTemp + Xsite) != 0)                                   //涓€閿熸枻鎷烽敓鏂ゆ嫹閿熻鐧界鎷烽敓鏂ゆ嫹鐩撮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
            break;
          else if (Xsite ==(ImageDeal[Ysite].RightBorder - 1))
          {
             ImageDeal[Ysite].IsLeftFind = 'T';
            break;
          }
        }
      if ((ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder) <=
          7)                              //鍥鹃敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹钖呴敓锟�
      {
        ImageStatus.OFFLine = Ysite + 1;  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋枩閿燂拷7灏忛敓鍓跨尨鎷烽敓鏂ゆ嫹鐩撮敓鎺ヨ鎷疯閿熸枻鎷�
        break;
      }
      if (ImageDeal[Ysite].IsRightFind == 'H')
        for (Xsite = (ImageDeal[Ysite].RightBorder - 1);
             Xsite >= (ImageDeal[Ysite].LeftBorder + 1); Xsite--) {
          if ((*(PicTemp + Xsite) == 0) && (*(PicTemp + Xsite - 1) != 0)) {
            ImageDeal[Ysite].RightBorder =
                Xsite;                    //閿熸枻鎷烽敓鏂ゆ嫹鍐堕敓鏂ゆ嫹鍙╅敓鏂ゆ嫹閿熺浼欐嫹閿熷彨榛戝府鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹涓洪敓鏂ゆ嫹閿熺殕鎲嬫嫹閿熸枻鎷风洿閿熸枻鎷峰彇閿熸枻鎷�
            ImageDeal[Ysite].IsRightFind = 'T';
            break;
          } else if (*(PicTemp + Xsite) != 0)
            break;
          else if (Xsite == (ImageDeal[Ysite].LeftBorder + 1))
          {
            ImageDeal[Ysite].RightBorder = Xsite;
            ImageDeal[Ysite].IsRightFind = 'T';
            break;
          }
        }
    }

 /***********閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熺潾鎲嬫嫹閿熸枻鎷�************/
    int ysite = 0;
    uint8 L_found_point = 0;
    uint8 R_found_point = 0;


    if(  ImageStatus.Road_type != Ramp)
    {
    if (    ImageDeal[Ysite].IsRightFind == 'W'
          &&Ysite > 10
          &&Ysite < 50
          &&ImageStatus.Road_type!=Barn_in
          )                     //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰€奸敓鏂ゆ嫹钖囬敓鏂ゆ嫹閿燂拷
    {
      if (Get_R_line == 'F')    //閿熸枻鎷蜂竴甯у浘閿熸枻鎷锋病閿熸枻鎷烽敓鏉扮櫢鎷烽敓鏂ゆ嫹閿熸枻鎷蜂竴閿熼樁纭锋嫹鍙╂媷閿熸枻鎷烽敓杞胯鎷烽敓鏂ゆ嫹閿熸枻鎷�
      {
        Get_R_line = 'T';       //閿熸枻鎷烽敓鏂ゆ嫹  涓€甯у浘閿熸枻鎷峰彧閿熸枻鎷蜂竴閿熸枻鎷� 閿熸枻鎷蜂负T
        ytemp_W_R = Ysite + 2;
        for (ysite = Ysite + 1; ysite < Ysite + 15; ysite++) {
          if (ImageDeal[ysite].IsRightFind =='T')  //閿熸枻鎷烽敓鐫唻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹  涓€閿熷閮介敓鏂ゆ嫹閿熷彨杈圭鎷�
            R_found_point++;
        }
        if (R_found_point >8)                      //閿熸彮纰夋嫹閿熸枻鎷峰噯鏂滈敓缁炴唻鎷�  閿熸枻鎷烽敓鎺ョ鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熺潾鎲嬫嫹   閿熸枻鎷烽敓鍙竟鐨勭鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹8
        {
          D_R = ((float)(ImageDeal[Ysite + R_found_point].RightBorder - ImageDeal[Ysite + 3].RightBorder)) /((float)(R_found_point - 3));
                                                  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹浜涢敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鏂滈敓鏂ゆ嫹
                                                  //閿熺煫闈╂嫹閿熺潾鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸帴绛规嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓闃讹拷
          if (D_R > 0) {
            R_Found_T ='T';                       //閿熸枻鎷烽敓鍙唻鎷疯殌閿熸枻鎷烽敓锟�0  閿熸枻鎷蜂箞閿熸彮纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓闃剁》鎷烽敓锟�  閿熸枻鎷蜂负閿熸枻鎷烽敓杞夸紮鎷烽敓鏂ゆ嫹
                                                  //閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨鎲嬫嫹铓€閿熸枻鎷烽敓锟�0  灏忛敓鏂ゆ嫹0閿熸枻鎷烽敓鏂ゆ嫹閿熸彮璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹鏄犻敓锟� 娌￠敓鏂ゆ嫹瑕�
          } else {
            R_Found_T = 'F';                      //娌￠敓鏂ゆ嫹閿熸彮纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熼樁纭锋嫹閿燂拷
            if (D_R < 0)
              ExtenRFlag = 'F';                   //閿熸枻鎷烽敓鏂ゆ嫹閿熻鐤氫紮鎷烽敓鏂ゆ嫹閿熺粸顕嗘嫹绾稿爲鎮寸櫢鎷烽敓锟�  閿熸枻鎷锋鍥鹃敓鏂ゆ嫹閿熸枻鎷烽敓鐭鎷�
          }
        }
      }
      if (R_Found_T == 'T')
        ImageDeal[Ysite].RightBorder =ImageDeal[ytemp_W_R].RightBorder -D_R * (ytemp_W_R - Ysite);  //閿熸枻鎷烽敓鏂ゆ嫹涓氶敓鏂ゆ嫹閿燂拷 閿熸枻鎷蜂箞閿熺殕浼欐嫹鍑嗛敓鏂ゆ嫹閿熸枻鎷烽敓鎺ョ鎷烽敓鏂ゆ嫹

      LimitL(ImageDeal[Ysite].RightBorder);  //閿熺潾鍑ゆ嫹
      LimitH(ImageDeal[Ysite].RightBorder);  //閿熺潾鍑ゆ嫹
    }

    if (ImageDeal[Ysite].IsLeftFind == 'W' && Ysite > 10 && Ysite < 50 &&
        ImageStatus.Road_type != Barn_in)    //閿熸枻鎷烽敓鏂ゆ嫹鍚岄敓鏂ゆ嫹  閿熸枻鎷峰憮閿燂拷
    {
      if (Get_L_line == 'F') {
        Get_L_line = 'T';
        ytemp_W_L = Ysite + 2;
        for (ysite = Ysite + 1; ysite < Ysite + 15; ysite++) {
          if (ImageDeal[ysite].IsLeftFind == 'T')
            L_found_point++;
        }
        if (L_found_point > 8)              //閿熸彮纰夋嫹閿熸枻鎷峰噯鏂滈敓缁炴唻鎷�  閿熸枻鎷烽敓鎺ョ鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熺潾鎲嬫嫹
        {
          D_L = ((float)(ImageDeal[Ysite + 3].LeftBorder -ImageDeal[Ysite + L_found_point].LeftBorder)) /((float)(L_found_point - 3));
          if (D_L > 0) {
            L_Found_T = 'T';

          } else {
            L_Found_T = 'F';
            if (D_L < 0)
              ExtenLFlag = 'F';
          }
        }
      }

      if (L_Found_T == 'T')
        ImageDeal[Ysite].LeftBorder =ImageDeal[ytemp_W_L].LeftBorder + D_L * (ytemp_W_L - Ysite);

      LimitL(ImageDeal[Ysite].LeftBorder);  //閿熺潾鍑ゆ嫹
      LimitH(ImageDeal[Ysite].LeftBorder);  //閿熺潾鍑ゆ嫹
    }
}
    if (ImageDeal[Ysite].IsLeftFind == 'W'&&ImageDeal[Ysite].IsRightFind == 'W')
         {
             ImageStatus.WhiteLine++;  //瑕侀敓鏂ゆ嫹閿熸枻鎷烽敓鎻鎷烽敓鐫竟锝忔嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�+1
         }
        if (ImageDeal[Ysite].IsLeftFind == 'W'&&Ysite<55)
        {
             ImageStatus.Left_Line++;
        }
        if (ImageDeal[Ysite].IsRightFind == 'W'&&Ysite<55)
        {
             ImageStatus.Right_Line++;
        }


      LimitL(ImageDeal[Ysite].LeftBorder);   //閿熺潾鍑ゆ嫹
      LimitH(ImageDeal[Ysite].LeftBorder);   //閿熺潾鍑ゆ嫹
      LimitL(ImageDeal[Ysite].RightBorder);  //閿熺潾鍑ゆ嫹
      LimitH(ImageDeal[Ysite].RightBorder);  //閿熺潾鍑ゆ嫹

      ImageDeal[Ysite].Wide =ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;
      ImageDeal[Ysite].Center =(ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2;

    if (ImageDeal[Ysite].Wide <= 7)         //閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熸枻鎷烽敓鎺ユ拝鎷烽敓鏂ゆ嫹
    {
      ImageStatus.OFFLine = Ysite + 1;
      break;
    }

    else if (  ImageDeal[Ysite].RightBorder <= 10
             ||ImageDeal[Ysite].LeftBorder >= 70) {
              ImageStatus.OFFLine = Ysite + 1;
              break;
    }                                        //閿熸枻鎷峰浘閿熸枻鎷烽敓鏂ゆ嫹閿熷彨鈽呮嫹閿燂拷0閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎻竟杈惧埌涓€閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鏃堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹姝㈠贰閿熸枻鎷�
  }


  return;
}

//閿熸帴绛规嫹閿熺浼欐嫹閿熺嫛锝忔嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹璇撮敓瑙掔尨鎷峰噯纭敓鏂ゆ嫹
static void DrawExtensionLine(void)        //閿熸枻鎷烽敓鏂ゆ嫹閿熸帴绛规嫹閿熺璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹 閿熸枻鎷烽敓绐栬鎷烽敓绔鎷烽敓鏂ゆ嫹鏂滈敓鏂ゆ嫹
{
  if ((
        ImageStatus.Road_type != Barn_in
        &&ImageStatus.Road_type != Ramp)
//        &&ImageStatus.pansancha_Lenth* OX==0
        &&ImageStatus.Road_type !=LeftCirque
        &&ImageStatus.Road_type !=RightCirque
        )                                  // g5.22  6.22閿熸枻鎷烽敓鏂ゆ嫹娉ㄩ敓鏂ゆ嫹  閿熻寰楁敼浼欐嫹閿熸枻鎷�
  {
    if (ImageStatus.WhiteLine >= ImageStatus.TowPoint_True - 15)
      TFSite = 55;
//    if (ImageStatus.CirqueOff == 'T' && ImageStatus.Road_type == LeftCirque)
//      TFSite = 55;
    if (ExtenLFlag != 'F')
      for (Ysite = 54; Ysite >= (ImageStatus.OFFLine + 4);
           Ysite--)                       //閿熸帴纰夋嫹閿熸枻鎷烽敓鍙尅鎷峰閿熸枻鎷烽敓鏂ゆ嫹鎵壂閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�   閿熸枻鎷峰熬閿熸枻鎷烽敓锟�
                                          //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰彧閿熸枻鎷蜂竴閿熸枻鎷�
      {
        PicTemp = Pixle[Ysite];           //閿熻姤褰撳墠閿熸枻鎷�
        if (ImageDeal[Ysite].IsLeftFind =='W')                          //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺鏂ゆ嫹娌℃壂閿熸枻鎷烽敓鏂ゆ嫹鎵敓鏂ゆ嫹閿熸枻鎷烽敓瑙掑府鎷疯壊閿熸枻鎷疯閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋病閿熸枻鎷烽敓鏂ゆ嫹鍛撻敓鏂ゆ嫹
        {
          //**************************************************//**************************************************
          if (ImageDeal[Ysite + 1].LeftBorder >= 70)                    //閿熸枻鎷烽敓鏂ゆ嫹閿熺鏂ゆ嫹瀹為敓鏂ゆ嫹閿熸枻鎷峰お閿熸彮鎲嬫嫹
          {
            ImageStatus.OFFLine = Ysite + 1;
            break;                        //鐩撮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
          }
          //************************************************//*************************************************

          while (Ysite >= (ImageStatus.OFFLine + 4))                    //閿熸枻鎷锋椂閿熸枻鎷锋病鎵敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
          {
            Ysite--;                      //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鎵�
            if (  ImageDeal[Ysite].IsLeftFind == 'T'
                &&ImageDeal[Ysite - 1].IsLeftFind == 'T'
                &&ImageDeal[Ysite - 2].IsLeftFind == 'T'
                &&ImageDeal[Ysite - 2].LeftBorder > 0
                &&ImageDeal[Ysite - 2].LeftBorder <70
                )                                                       //閿熸枻鎷烽敓缂搭煉鎷烽敓鏂ゆ嫹閿熸枻鎷疯皭閿熸枻鎷烽敓鏂ゆ嫹鐬敓鏂ゆ嫹鍐堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍗搁敓鏂ゆ嫹閿熸枻鎷烽敓绔枻鎷锋倴顭掓嫹閿熺鏂ゆ嫹閿熻妭绌哄府鎷烽敓杈冨嚖鎷烽敓鏂ゆ嫹
            {
              FTSite = Ysite - 2;          //閿熺獤鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷风墶璇欓敓鏂ゆ嫹鍐欓敓鏂ゆ嫹閿熺唇Tsite
              break;
            }
          }

          DetL =
              ((float)(ImageDeal[FTSite].LeftBorder -
                       ImageDeal[TFSite].LeftBorder)) /
              ((float)(FTSite - TFSite));  //閿熸枻鎷峰憮閿熸枻鎷锋枩閿熺粸锝忔嫹閿熷彨纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷/閿熷彨纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
          if (FTSite > ImageStatus.OFFLine)
            for (
                ytemp = TFSite; ytemp >= FTSite; ytemp--)               //閿熸帴纰夋嫹涓€閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰憮閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯瘷閿熸枻鎷锋閿熸枻鎷烽敓鏂ゆ嫹鏄曨€╃》鎷烽敓鏂ゆ嫹閿熺即銊栨唻鎷烽敓鏂ゆ嫹鐬婚敓鏂ゆ嫹鎴忛敓鏂ゆ嫹閿熸枻鎷烽敓绔枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻锟�
            {
              ImageDeal[ytemp].LeftBorder =
                  (int)(DetL * ((float)(ytemp - TFSite))) +
                  ImageDeal[TFSite]
                      .LeftBorder;                                      //閿熸枻鎷烽敓鏂ゆ嫹閿熻妭纭锋嫹鐩灮鐘堕敓鏂ゆ嫹閿熸枻鎷锋捀閿熸枻鎷烽敓鍙唻鎷锋捀閿熸枻鎷烽敓渚ュ尅鎷烽敓鏂ゆ嫹娆犻敓鏂ゆ嫹閿熼叺纭锋嫹閿熸枻鎷烽敓锟�
            }
        } else
          TFSite = Ysite + 2;                                           //閿熸枻鎷烽敓缂搭煉鎷烽敓鏂ゆ嫹鍚敓鏂ゆ嫹姊伴敓鏂ゆ嫹閿熺鐣岋紝閿熸枻鎷烽敓鍙揪鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻姤锛岄敓鏂ゆ嫹閿熸枻鎷锋枩閿熺粸锝忔嫹
      }

    if (ImageStatus.WhiteLine >= ImageStatus.TowPoint_True - 15)
      TFSite = 55;
    // g5.22
    if (ImageStatus.CirqueOff == 'T' && ImageStatus.Road_type == RightCirque)
      TFSite = 55;
    if (ExtenRFlag != 'F')
      for (Ysite = 54; Ysite >= (ImageStatus.OFFLine + 4);
           Ysite--)               //閿熸帴纰夋嫹閿熸枻鎷烽敓鍙尅鎷峰閿熸枻鎷烽敓鏂ゆ嫹鎵壂閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
      {
        PicTemp = Pixle[Ysite];  //閿熻姤褰撳墠閿熸枻鎷�

        if (ImageDeal[Ysite].IsRightFind =='W')                       //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍐跺憮閿熺煫绨ь煉鎷烽敓鏂ゆ嫹閿熺即顭掓嫹閿熸枻鎷烽敓鏂ゆ嫹鍓嶉敓缂搭偓鎷烽敓鍓跨鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鐭紮鎷烽敓鏂ゆ嫹鍐跺憮閿熷锛岄敓鏂ゆ嫹閿熻杈炬嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鑺傜鎷�
        {
          if (ImageDeal[Ysite + 1].RightBorder <= 10)                 //閿熸枻鎷烽敓鏂ゆ嫹鍐跺憮閿熺粸纰夋嫹閿熸枻鎷烽敓鏁欘偓鎷烽敓鏂ゆ嫹
          {
            ImageStatus.OFFLine =Ysite + 1;                           //鐩撮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
            break;
          }
          while (Ysite >= (ImageStatus.OFFLine + 4))                  //閿熸枻鎷锋椂閿熸枻鎷锋病鎵敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
          {
            Ysite--;
            if (  ImageDeal[Ysite].IsRightFind == 'T'
                &&ImageDeal[Ysite - 1].IsRightFind == 'T'
                &&ImageDeal[Ysite - 2].IsRightFind == 'T'
                &&ImageDeal[Ysite - 2].RightBorder < 70
                &&ImageDeal[Ysite - 2].RightBorder > 10
                )                                                      //閿熸枻鎷烽敓缂搭煉鎷烽敓鏂ゆ嫹閿熸枻鎷疯皭閿熸枻鎷烽敓鏂ゆ嫹鐬敓鏂ゆ嫹鍐堕敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍗搁敓鏂ゆ嫹閿熸枻鎷烽敓绔枻鎷锋倴顭掓嫹閿熺鏂ゆ嫹閿熻妭绌哄府鎷烽敓杈冨嚖鎷烽敓鏂ゆ嫹
            {
              FTSite = Ysite - 2;                                      // 閿熺獤鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷风墶璇欓敓鏂ゆ嫹鍐欓敓鏂ゆ嫹閿熺唇Tsite
              break;
            }
          }

          DetR =((float)(ImageDeal[FTSite].RightBorder -ImageDeal[TFSite].RightBorder)) /((float)(FTSite - TFSite));         //閿熸彮杈规枻鎷烽敓鍙唻鎷峰墿閿熸枻鎷锋閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�/閿熷彨纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
          if (FTSite > ImageStatus.OFFLine)
            for (ytemp = TFSite; ytemp >= FTSite;ytemp--)              //閿熸帴纰夋嫹涓€閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿熸彮杈规枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鑺傝鎷烽敓鍙鎷烽敓鏂ゆ嫹閿熺枼寮€濮嬮敓鏂ゆ嫹閿熸枻鎷锋壂鐩撮敓鏂ゆ嫹閿熺Ц甯嫹閿熻緝鍑ゆ嫹閿熸枻鎷烽敓鎻竟鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓琛楋拷
            {
              ImageDeal[ytemp].RightBorder =(int)(DetR * ((float)(ytemp - TFSite))) +ImageDeal[TFSite].RightBorder;          //閿熸枻鎷烽敓鏂ゆ嫹閿熻妭纭锋嫹鐩灮鐘堕敓鏂ゆ嫹閿熸枻鎷锋捀閿熸枻鎷烽敓鍙唻鎷锋捀閿熸枻鎷烽敓渚ュ尅鎷烽敓鏂ゆ嫹娆犻敓鏂ゆ嫹閿熼叺纭锋嫹閿熸枻鎷烽敓锟�
            }
        } else
          TFSite =Ysite +2;                                           //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋閿熸枻鎷峰喍鍛撻敓鏂ゆ嫹涓氶敓鏂ゆ嫹鑰嶉敓鏂ゆ嫹閿熺獤闈╂嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯瘷閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閫忛敓绲婩site
      }
  }
  for (Ysite = 59; Ysite >= ImageStatus.OFFLine; Ysite--) {
    ImageDeal[Ysite].Center =(ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) /2;                                //鎵敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸彮浼欐嫹姒叏鎷峰憰閿熻顕嗘嫹閿熸枻鎷烽敓鍙》鎷峰€奸敓鏂ゆ嫹閿熸枻鎷�
    ImageDeal[Ysite].Wide =-ImageDeal[Ysite].LeftBorder +ImageDeal[Ysite].RightBorder;                                       //閿熸枻鎷烽敓鑴氫紮鎷蜂箣閿熸枻鎷风洰閿熸枻鎷峰嵈閿熸枻鎷烽敓锟�
  }
}
/*閿熻緝鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓琛楀嚖鎷烽敓鏂ゆ嫹鎵敓绔綇鎷烽敓鏂ゆ嫹涓洪敓鏂ゆ嫹閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熷彨璁规嫹鍏冮敓鎴殑绗鎷烽敓鏂ゆ嫹閿熸枻鎷�*/
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name           Search_Bottom_Line_OTSU
//  @brief          閿熸枻鎷峰彇閿熼樁璇ф嫹閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹
//  @param          imageInput[IMAGE_ROW][IMAGE_COL]        閿熸枻鎷烽敓鏂ゆ嫹閿熼叺纭锋嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
//  @param          Row                                     鍥鹃敓鏂ゆ嫹閿熺祼site
//  @param          Col                                     鍥鹃敓鏂ゆ嫹閿熺祻site
//  @return         Bottonline                              閿熼樁鎲嬫嫹閿熸枻鎷烽€夐敓鏂ゆ嫹
//  @time           2022閿熸枻鎷�10閿熸枻鎷�9閿熸枻鎷�
//  @Author
//  Sample usage:   Search_Bottom_Line_OTSU(imageInput, Row, Col, Bottonline);
//--------------------------------------------------------------------------------------------------------------------------------------------

void Search_Bottom_Line_OTSU(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline)
{

    //瀵婚敓鏂ゆ嫹閿熸枻鎷峰紤鍛撻敓锟�
    for (int Xsite = Col / 2-2; Xsite > 1; Xsite--)
    {
        if (imageInput[Bottonline][Xsite] == 1 && imageInput[Bottonline][Xsite - 1] == 0)
        {
            ImageDeal[Bottonline].LeftBoundary = Xsite;//閿熸枻鎷峰彇閿熼樁鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
            break;
        }
    }
    for (int Xsite = Col / 2+2; Xsite < LCDW-1; Xsite++)
    {
        if (imageInput[Bottonline][Xsite] == 1 && imageInput[Bottonline][Xsite + 1] == 0)
        {
            ImageDeal[Bottonline].RightBoundary = Xsite;//閿熸枻鎷峰彇閿熼樁鎲嬫嫹閿熸彮鎲嬫嫹閿熸枻鎷�
            break;
        }
    }

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name           Search_Left_and_Right_Lines
//  @brief          閫氶敓鏂ゆ嫹sobel閿熸枻鎷峰彇閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹
//  @param          imageInput[IMAGE_ROW][IMAGE_COL]        閿熸枻鎷烽敓鏂ゆ嫹閿熼叺纭锋嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
//  @param          Row                                     鍥鹃敓鏂ゆ嫹閿熺祼site
//  @param          Col                                     鍥鹃敓鏂ゆ嫹閿熺祻site
//  @param          Bottonline                              閿熼樁鎲嬫嫹閿熸枻鎷烽€夐敓鏂ゆ嫹
//  @return         閿熸枻鎷�
//  @time           2022閿熸枻鎷�10閿熸枻鎷�7閿熸枻鎷�
//  @Author
//  Sample usage:   Search_Left_and_Right_Lines(imageInput, Row, Col, Bottonline);
//--------------------------------------------------------------------------------------------------------------------------------------------

void Search_Left_and_Right_Lines(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline)
{
    //閿熸枻鎷烽敓鏂ゆ嫹灏忛敓鍓跨殑纰夋嫹鍓嶉敓鏂ゆ嫹閿熸枻鎷风姸鎬佷綅閿熸枻鎷蜂负 閿熸枻鎷� 閿熸枻鎷� 閿熸枻鎷� 閿熸枻鎷� 涓€閿熸枻鎷疯閿熸枻鎷� 閿熻緝锝忔嫹閿熸枻鎷烽敓杞款亷鎷烽敓缂达拷 閿熸枻鎷烽敓杈冩唻鎷蜂负閿熸枻鎷疯壊 閿熼摪锝忔嫹閿熸彮鎲嬫嫹涓鸿壊  閿熸彮锝忔嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨鐚存嫹鑹�
/*  鍓嶉敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻棄锛�
                *   0
                * 3   1
                *   2
*/
/*瀵婚敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷*/
    uint8 Left_Rule[2][8] = {
                                  {0,-1,1,0,0,1,-1,0 },//{0,-1},{1,0},{0,1},{-1,0},  (x,y )
                                  {-1,-1,1,-1,1,1,-1,1} //{-1,-1},{1,-1},{1,1},{-1,1}
    };
    /*瀵婚敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷*/
    int Right_Rule[2][8] = {
                              {0,-1,1,0,0,1,-1,0 },//{0,-1},{1,0},{0,1},{-1,0},
                              {1,-1,1,1,-1,1,-1,-1} //{1,-1},{1,1},{-1,1},{-1,-1}
    };
      int num=0;
    uint8 Left_Ysite = Bottonline;
    uint8 Left_Xsite = ImageDeal[Bottonline].LeftBoundary;
    uint8 Left_Rirection = 0;//閿熸枻鎷峰徎閿熸枻鎷烽敓锟�
    uint8 Pixel_Left_Ysite = Bottonline;
    uint8 Pixel_Left_Xsite = 0;

    uint8 Right_Ysite = Bottonline;
    uint8 Right_Xsite = ImageDeal[Bottonline].RightBoundary;
    uint8 Right_Rirection = 0;//閿熸彮杈瑰嚖鎷烽敓鏂ゆ嫹
    uint8 Pixel_Right_Ysite = Bottonline;
    uint8 Pixel_Right_Xsite = 0;
    uint8 Ysite = Bottonline;
    ImageStatus.OFFLineBoundary = 5;
    while (1)
    {
            num++;
            if(num>400)
            {
                 ImageStatus.OFFLineBoundary = Ysite;
                break;
            }
        if (Ysite >= Pixel_Left_Ysite && Ysite >= Pixel_Right_Ysite)
        {
            if (Ysite < ImageStatus.OFFLineBoundary)
            {
                ImageStatus.OFFLineBoundary = Ysite;
                break;
            }
            else
            {
                Ysite--;
            }
        }
        /*********閿熸枻鎷烽敓绐栬鎷烽敓锟�*******/
        if ((Pixel_Left_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary)//閿熸彮鎲嬫嫹鎵敓鏂ゆ嫹
        {
            /*閿熸枻鎷烽敓鏂ゆ嫹鍓嶉敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹*/
            Pixel_Left_Ysite = Left_Ysite + Left_Rule[0][2 * Left_Rirection + 1];
            Pixel_Left_Xsite = Left_Xsite + Left_Rule[0][2 * Left_Rirection];

            if (imageInput[Pixel_Left_Ysite][Pixel_Left_Xsite] == 0)//鍓嶉敓鏂ゆ嫹閿熻鐚存嫹鑹�
            {
                //椤烘椂閿熸枻鎷烽敓鏂ゆ嫹杞�90
                if (Left_Rirection == 3)
                    Left_Rirection = 0;
                else
                    Left_Rirection++;
            }
            else//鍓嶉敓鏂ゆ嫹閿熻甯嫹鑹�
            {
                /*閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰墠閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�*/
                Pixel_Left_Ysite = Left_Ysite + Left_Rule[1][2 * Left_Rirection + 1];
                Pixel_Left_Xsite = Left_Xsite + Left_Rule[1][2 * Left_Rirection];

                if (imageInput[Pixel_Left_Ysite][Pixel_Left_Xsite] == 0)//閿熸枻鎷峰墠閿熸枻鎷蜂负閿熸枻鎷疯壊
                {
                    //閿熸枻鎷烽敓娲ヤ笉鎲嬫嫹  Left_Rirection
                    Left_Ysite = Left_Ysite + Left_Rule[0][2 * Left_Rirection + 1];
                    Left_Xsite = Left_Xsite + Left_Rule[0][2 * Left_Rirection];
                    if (ImageDeal[Left_Ysite].LeftBoundary_First == 0){
                        ImageDeal[Left_Ysite].LeftBoundary_First = Left_Xsite;
                        ImageDeal[Left_Ysite].LeftBoundary = Left_Xsite;
                    }
                }
                else//閿熸枻鎷峰墠閿熸枻鎷蜂负閿熸枻鎷疯壊
                {
                    // 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓渚ユ唻鎷� Left_Rirection  閿熸枻鎷锋椂閿熸枻鎷�90閿熸枻鎷�
                    Left_Ysite = Left_Ysite + Left_Rule[1][2 * Left_Rirection + 1];
                    Left_Xsite = Left_Xsite + Left_Rule[1][2 * Left_Rirection];
                    if (ImageDeal[Left_Ysite].LeftBoundary_First == 0 )
                        ImageDeal[Left_Ysite].LeftBoundary_First = Left_Xsite;
                    ImageDeal[Left_Ysite].LeftBoundary = Left_Xsite;
                    if (Left_Rirection == 0)
                        Left_Rirection = 3;
                    else
                        Left_Rirection--;
                }

            }
        }
        /*********閿熸彮鎲嬫嫹宸￠敓鏂ゆ嫹*******/
        if ((Pixel_Right_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary)//閿熸彮鎲嬫嫹鎵敓鏂ゆ嫹
        {
            /*閿熸枻鎷烽敓鏂ゆ嫹鍓嶉敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹*/
            Pixel_Right_Ysite = Right_Ysite + Right_Rule[0][2 * Right_Rirection + 1];
            Pixel_Right_Xsite = Right_Xsite + Right_Rule[0][2 * Right_Rirection];

            if (imageInput[Pixel_Right_Ysite][Pixel_Right_Xsite] == 0)//鍓嶉敓鏂ゆ嫹閿熻鐚存嫹鑹�
            {
                //閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹杞�90
                if (Right_Rirection == 0)
                    Right_Rirection = 3;
                else
                    Right_Rirection--;
            }
            else//鍓嶉敓鏂ゆ嫹閿熻甯嫹鑹�
            {
                /*閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰墠閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�*/
                Pixel_Right_Ysite = Right_Ysite + Right_Rule[1][2 * Right_Rirection + 1];
                Pixel_Right_Xsite = Right_Xsite + Right_Rule[1][2 * Right_Rirection];

                if (imageInput[Pixel_Right_Ysite][Pixel_Right_Xsite] == 0)//閿熸枻鎷峰墠閿熸枻鎷蜂负閿熸枻鎷疯壊
                {
                    //閿熸枻鎷烽敓娲ヤ笉鎲嬫嫹  Right_Rirection
                    Right_Ysite = Right_Ysite + Right_Rule[0][2 * Right_Rirection + 1];
                    Right_Xsite = Right_Xsite + Right_Rule[0][2 * Right_Rirection];
                    if (ImageDeal[Right_Ysite].RightBoundary_First == 79 )
                        ImageDeal[Right_Ysite].RightBoundary_First = Right_Xsite;
                    ImageDeal[Right_Ysite].RightBoundary = Right_Xsite;
                }
                else//閿熸枻鎷峰墠閿熸枻鎷蜂负閿熸枻鎷疯壊
                {
                    // 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓渚ユ唻鎷� Right_Rirection  閿熸枻鎷锋椂閿熸枻鎷�90閿熸枻鎷�
                    Right_Ysite = Right_Ysite + Right_Rule[1][2 * Right_Rirection + 1];
                    Right_Xsite = Right_Xsite + Right_Rule[1][2 * Right_Rirection];
                    if (ImageDeal[Right_Ysite].RightBoundary_First == 79)
                        ImageDeal[Right_Ysite].RightBoundary_First = Right_Xsite;
                    ImageDeal[Right_Ysite].RightBoundary = Right_Xsite;
                    if (Right_Rirection == 3)
                        Right_Rirection = 0;
                    else
                        Right_Rirection++;
                }

            }
        }

        if (abs(Pixel_Right_Xsite - Pixel_Left_Xsite) < 3)//Ysite<80閿熸枻鎷蜂负閿熷壙鍑ゆ嫹閿熻妭搴曡鎷烽敓瑙掑府鎷烽敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷烽敓鏂ゆ嫹閿燂拷  3 && Ysite < 30
        {

            ImageStatus.OFFLineBoundary = Ysite;
            break;
        }

    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name           Search_Border_OTSU
//  @brief          閫氶敓鏂ゆ嫹OTSU閿熸枻鎷峰彇閿熸枻鎷烽敓鏂ゆ嫹 閿熸枻鎷烽敓鏂ゆ嫹鎭�
//  @param          imageInput[IMAGE_ROW][IMAGE_COL]        閿熸枻鎷烽敓鏂ゆ嫹閿熼叺纭锋嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
//  @param          Row                                     鍥鹃敓鏂ゆ嫹閿熺祼site
//  @param          Col                                     鍥鹃敓鏂ゆ嫹閿熺祻site
//  @param          Bottonline                              閿熼樁鎲嬫嫹閿熸枻鎷烽€夐敓鏂ゆ嫹
//  @return         閿熸枻鎷�
//  @time           2022閿熸枻鎷�10閿熸枻鎷�7閿熸枻鎷�
//  @Author
//  Sample usage:   Search_Border_OTSU(mt9v03x_image, IMAGE_ROW, IMAGE_COL, IMAGE_ROW-8);
//--------------------------------------------------------------------------------------------------------------------------------------------

void Search_Border_OTSU(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline)
{
    ImageStatus.WhiteLine_L = 0;
    ImageStatus.WhiteLine_R = 0;
    //ImageStatus.OFFLine = 1;
    /*閿熸枻鎷烽敓鏂ゆ嫹閿熼摪杈圭晫澶勯敓鏂ゆ嫹*/
    for (int Xsite = 0; Xsite < LCDW; Xsite++)
    {
        imageInput[0][Xsite] = 0;
        imageInput[Bottonline + 1][Xsite] = 0;
    }
    /*閿熸枻鎷烽敓鏂ゆ嫹閿熸彮杈圭晫澶勯敓鏂ゆ嫹*/
    for (int Ysite = 0; Ysite < LCDH; Ysite++)
    {
            ImageDeal[Ysite].LeftBoundary_First = 0;
            ImageDeal[Ysite].RightBoundary_First = 79;

            imageInput[Ysite][0] = 0;
            imageInput[Ysite][LCDW - 1] = 0;
    }
    /********閿熸枻鎷峰彇閿熼樁璇ф嫹閿熸枻鎷烽敓鏂ゆ嫹*********/
    Search_Bottom_Line_OTSU(imageInput, Row, Col, Bottonline);
    /********閿熸枻鎷峰彇閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹*********/
    Search_Left_and_Right_Lines(imageInput, Row, Col, Bottonline);



    for (int Ysite = Bottonline; Ysite > ImageStatus.OFFLineBoundary + 1; Ysite--)
    {
        if (ImageDeal[Ysite].LeftBoundary < 3)
        {
            ImageStatus.WhiteLine_L++;
        }
        if (ImageDeal[Ysite].RightBoundary > LCDW - 3)
        {
            ImageStatus.WhiteLine_R++;
        }
    }
}

//閿熸枻鎷烽敓琛楄鎷烽敓绔鎷锋椂閿熸枻鎷�  閿熸枻鎷烽敓鏂ゆ嫹纭敓鏂ゆ嫹閿熺潾鎲嬫嫹閿熷彨纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹
static void RouteFilter(void) {
//  if(ImageStatus.Road_type != RightCirque && ImageStatus.Road_type != LeftCirque)
//  {
  for (Ysite = 58; Ysite >= (ImageStatus.OFFLine + 5);   //鍘熼敓鏂ゆ嫹58
       Ysite--)                                     //閿熸帴鍖℃嫹濮嬩綅閿熸枻鎷峰仠姝綅
  {
    if (   ImageDeal[Ysite].IsLeftFind == 'W'
         &&ImageDeal[Ysite].IsRightFind == 'W'
         &&Ysite <= 45
         &&ImageDeal[Ysite - 1].IsLeftFind == 'W'
         &&ImageDeal[Ysite - 1].IsRightFind =='W')  //閿熸枻鎷峰墠閿熸枻鎷烽敓鏂ゆ嫹閿熸彮璁规嫹閿熺潾杈癸綇鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍓�45閿熸枻鎷�   閿熷壙璇ф嫹
    {
      ytemp = Ysite;
      while (ytemp >= (ImageStatus.OFFLine +5))     // 閿熶茎闈╂嫹閿熸枻鎷烽敓鐨嗭綇鎷�-6鏁堥敓鏂ゆ嫹閿熸枻鎷蜂竴浜�   鍘熼敓鏂ゆ嫹+5
      {
        ytemp--;
        if (  ImageDeal[ytemp].IsLeftFind == 'T'
            &&ImageDeal[ytemp].IsRightFind == 'T')  //瀵婚敓鏂ゆ嫹閿熸枻鎷烽敓绔鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓渚ワ綇鎷烽敓鎻鎷烽敓璇湰閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋湪绛掗敓鏂ゆ嫹閿熸枻鎷烽敓锟�
        {
          DetR = (float)(ImageDeal[ytemp - 1].Center - ImageDeal[Ysite + 2].Center) /(float)(ytemp - 1 - Ysite - 2);          //閿熸枻鎷锋枩閿熸枻鎷�
          int CenterTemp = ImageDeal[Ysite + 2].Center;
          int LineTemp = Ysite + 2;
          while (Ysite >= ytemp) {
            ImageDeal[Ysite].Center =(int)(CenterTemp +DetR * (float)(Ysite - LineTemp));                                     //閿熸枻鎷锋枩閿熺粸璇ф嫹
            Ysite--;
          }
          break;
        }
      }
    }
    ImageDeal[Ysite].Center =(ImageDeal[Ysite - 1].Center + 2 * ImageDeal[Ysite].Center) /3;                                  //閿熸枻鎷峰钩閿熸枻鎷烽敓鏂ゆ嫹搴旈敓鐭紮鎷峰唹鍖ｉ敓锟�  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰钩閿熸枻鎷�
  }
//  }
}

int icm_start_test_cross = 0;  //閿熸枻鎷烽敓鏂ゆ嫹icm閿熸枻鎷烽敓琛楁唻鎷峰織浣�

/****鍗侀敓琛楃》鎷烽敓锟�*****/  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋兇顭掓嫹涓敓鏂ゆ嫹椤洪敓鏂ゆ嫹閿熺粸顕嗘嫹閿燂拷  閿熸磥褰撻敓鑺傝鎷疯閿熸枻鎷烽敓鏂ゆ嫹
void Cross_Test() {
  if (ImageStatus.OFFLine > 15)                       //閿熸枻鎷烽敓鏂ゆ嫹閿熸帴鎾呮嫹閿熸枻鎷峰唹杈栭敓鏂ゆ嫹閿熺粸鎲嬫嫹閿燂拷 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓琛楄揪鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓瑙ｅ閿熸枻鎷�270閿熸枻鎷烽敓鏂ゆ嫹閿熻顕嗘嫹閿熸枻鎷峰崄閿熸枻鎷�
    icm_start_test_cross = 1;
  else
    icm_start_test_cross = 0;

  if (abs(tuoluoyijifen) > 100)
    ImageStatus.Road_type = Cross;
//  if (ImageStatus.Road_type == Cross && ImageStatus.Cross_Lenth * OX > 100)
//    ImageStatus.Road_type = 0;
}

//閿熸枻鎷峰彇閿熸枻鎷烽敓鍙粦纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鐭紮鎷烽敓鏂ゆ嫹鐜敓锟�
int Black_Point = 0;
int Black_Point_ALL = 0;
void GetBlack_Point()
{
  for (Ysite = 59; Ysite > 0; Ysite--) {
    PicTemp = Pixle[Ysite];
    for (Xsite = 0; Xsite < 80; Xsite++) {
      if (*(PicTemp + Xsite) == 0)
        Black_Point++;
    }
    Black_Point_ALL = Black_Point_ALL + Black_Point;
    ImageDeal[Ysite].Black_Point = Black_Point;
    Black_Point = 0;
  }
  ImageStatus.Black_Pro_ALL = Black_Point_ALL / 48;
  Black_Point_ALL = 0;
}


 //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�   閿熸枻鎷烽敓鐭紮鎷烽敓鏂ゆ嫹鐜敓锟�
void GetClose_Bord()
{
  for (Ysite = 59; Ysite > 0; Ysite--) {
    PicTemp = Pixle[Ysite];

    for (Xsite = 0; Xsite < ImageStatus.MiddleLine; Xsite++) {
      if (*(PicTemp + Xsite) == 0 && (*(PicTemp + Xsite + 1) == 1) &&
          (*(PicTemp + Xsite + 2) == 1)) {
        ImageDeal[Ysite].close_LeftBorder = Xsite;
        break;
      } else ImageDeal[Ysite].close_LeftBorder = 0;
    }
    for (Xsite = 79; Xsite > ImageStatus.MiddleLine; Xsite--) {
      if (*(PicTemp + Xsite) == 0 && (*(PicTemp + Xsite - 1) == 1) &&
          (*(PicTemp + Xsite - 2) == 1)) {
        ImageDeal[Ysite].close_RightBorder = Xsite;
        break;
      } else
        ImageDeal[Ysite].close_RightBorder = 79;
    }

    //閿熸彮鍑ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
    for (Xsite = ImageDeal[Ysite].close_LeftBorder + 1;
         Xsite < ImageStatus.MiddleLine; Xsite++) {
      if (*(PicTemp + Xsite) == 1 && (*(PicTemp + Xsite + 1) == 0) &&
          (*(PicTemp + Xsite + 2) == 0)) {
        ImageDeal[Ysite].opp_LeftBorder = Xsite;
        break;
      } else
        ImageDeal[Ysite].opp_LeftBorder = ImageDeal[Ysite].close_LeftBorder + 1;
    }

    for (Xsite = ImageDeal[Ysite].close_RightBorder - 1;
         Xsite > ImageStatus.MiddleLine; Xsite--) {
      if (*(PicTemp + Xsite) == 1 && (*(PicTemp + Xsite - 1) == 0) &&
          (*(PicTemp + Xsite - 2) == 0)) {
        ImageDeal[Ysite].opp_RightBorder = Xsite;
        break;
      } else
        ImageDeal[Ysite].opp_RightBorder =
            ImageDeal[Ysite].close_RightBorder - 1;
    }
  }
}

/****鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓锟�***/
uint8 Pass_flag = 'F';
//uint8 Left_Less_Num = 0;
//閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
int ceshi_flag;
//--------------------------------------------------------------
//  @name           Element_Judgment_Left_Rings()
//  @brief          閿熸枻鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹閿熷彨鏂鎷烽敓鎺ョ尨鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹.
//  @parameter      void
//  @time
//  @Author         MRCHEN
//  Sample usage:   Element_Judgment_Left_Rings();
//-------------------------------------------------------------
void Element_Judgment_Left_Rings()
{
    if(ImageStatus.Right_Line > 6
     ||ImageStatus.Left_Line < 15 // 13
     ||ImageStatus.OFFLine > 10
    // ||variance_acc>30
     || Straight_Judge(2, 30, 45) > 1
     || ImageStatus.WhiteLine>8
//     || ImageDeal[52].IsLeftFind == 'W'
//     || ImageDeal[53].IsLeftFind == 'W'
     || ImageDeal[54].IsLeftFind == 'W'
     || ImageDeal[55].IsLeftFind == 'W'
     || ImageDeal[56].IsLeftFind == 'W'
     || ImageDeal[57].IsLeftFind == 'W'
     || ImageDeal[58].IsLeftFind == 'W'
     )
        return;
    int ring_ysite = 25;
    Left_RingsFlag_Point1_Ysite = 0;
    Left_RingsFlag_Point2_Ysite = 0;
    for (int Ysite = 58; Ysite > ring_ysite; Ysite--)
    {
        if (ImageDeal[Ysite].LeftBoundary_First - ImageDeal[Ysite - 1].LeftBoundary_First > 4)
        {
            Left_RingsFlag_Point1_Ysite = Ysite;
            break;
        }
    }
    for (int Ysite = 58; Ysite > ring_ysite; Ysite--)
    {
        if (ImageDeal[Ysite + 1].LeftBoundary - ImageDeal[Ysite].LeftBoundary > 4)
        {
            Left_RingsFlag_Point2_Ysite = Ysite;
            break;
        }
    }
    for (int Ysite = Left_RingsFlag_Point1_Ysite; Ysite > ImageStatus.OFFLine; Ysite--)
    {
        if (   ImageDeal[Ysite + 6].LeftBorder < ImageDeal[Ysite + 3].LeftBorder
            && ImageDeal[Ysite + 5].LeftBorder < ImageDeal[Ysite + 3].LeftBorder
            && ImageDeal[Ysite + 3].LeftBorder > ImageDeal[Ysite + 2].LeftBorder
            && ImageDeal[Ysite + 3].LeftBorder > ImageDeal[Ysite + 1].LeftBorder)
        {
            Ring_Help_Flag = 1;
            break;
        }
    }
    if(Left_RingsFlag_Point2_Ysite > Left_RingsFlag_Point1_Ysite+1 && Ring_Help_Flag == 0 )
    {
        if(ImageStatus.Left_Line > 7)//13
            Ring_Help_Flag = 1;
    }
    if (Left_RingsFlag_Point2_Ysite > Left_RingsFlag_Point1_Ysite+1 && Ring_Help_Flag == 1 && ImageFlag.image_element_rings_flag ==0)
    {
        ImageFlag.image_element_rings = 1;
        ImageFlag.image_element_rings_flag = 1;
        ImageFlag.ring_big_small=1;
        ImageStatus.Road_type = LeftCirque;
    }
    Ring_Help_Flag = 0;
}

//--------------------------------------------------------------
//  @name           Element_Judgment_Right_Rings()
//  @brief          閿熸枻鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹閿熷彨鏂鎷烽敓鎺ョ尨鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹.
//  @parameter      void
//  @time
//  @Author         MRCHEN
//  Sample usage:   Element_Judgment_Right_Rings();
//--------------------------------------------------------------
void Element_Judgment_Right_Rings()
{
    if (   ImageStatus.Left_Line > 8
        || ImageStatus.Right_Line < 15 //13
        || ImageStatus.OFFLine >10
        || Straight_Judge(1, 25, 45) > 1
    //    ||variance_acc>18
        || ImageStatus.WhiteLine>8
        || ImageDeal[52].IsRightFind == 'W'
        || ImageDeal[53].IsRightFind == 'W'
        || ImageDeal[54].IsRightFind == 'W'
        || ImageDeal[55].IsRightFind == 'W'
        || ImageDeal[56].IsRightFind == 'W'
        || ImageDeal[57].IsRightFind == 'W'
        || ImageDeal[58].IsRightFind == 'W')
        {return;}
    int ring_ysite = 25;
    Right_RingsFlag_Point1_Ysite = 0;
    Right_RingsFlag_Point2_Ysite = 0;
    for (int Ysite = 58; Ysite > ring_ysite; Ysite--)
    {
        if (ImageDeal[Ysite - 1].RightBoundary_First - ImageDeal[Ysite].RightBoundary_First > 4)
        {
            Right_RingsFlag_Point1_Ysite = Ysite;
            break;
        }
    }
    for (int Ysite = 58; Ysite > ring_ysite; Ysite--)
    {
        if (ImageDeal[Ysite].RightBoundary - ImageDeal[Ysite + 1].RightBoundary > 4)
        {
            Right_RingsFlag_Point2_Ysite = Ysite;
            break;
        }
    }
    for (int Ysite = Right_RingsFlag_Point1_Ysite; Ysite > 10; Ysite--)
    {
        if (   ImageDeal[Ysite + 6].RightBorder > ImageDeal[Ysite + 3].RightBorder
            && ImageDeal[Ysite + 5].RightBorder > ImageDeal[Ysite + 3].RightBorder
            && ImageDeal[Ysite + 3].RightBorder < ImageDeal[Ysite + 2].RightBorder
            && ImageDeal[Ysite + 3].RightBorder < ImageDeal[Ysite + 1].RightBorder
           )
        {
            Ring_Help_Flag = 1;
            break;
        }
    }
    if(Right_RingsFlag_Point2_Ysite > Right_RingsFlag_Point1_Ysite+1 && Ring_Help_Flag == 0)
    {
        if(ImageStatus.Right_Line>7)
            Ring_Help_Flag = 1;
    }
    if (Right_RingsFlag_Point2_Ysite > Right_RingsFlag_Point1_Ysite+1 && Ring_Help_Flag == 1 && ImageFlag.image_element_rings_flag == 0)
    {

        ImageFlag.image_element_rings = 2;
        ImageFlag.image_element_rings_flag = 1;
        ImageFlag.ring_big_small=1;     //灏忛敓鏂ゆ嫹
        ImageStatus.Road_type = RightCirque;
    }
    Ring_Help_Flag = 0;
}
//閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
void Element_Handle_Left_Rings(void)
{
    /***************************************閿熸枻鎷烽敓鏂ゆ嫹**************************************/
    int num = 0;
    for (int Ysite = 55; Ysite > 30; Ysite--)
    {
        if(ImageDeal[Ysite].IsLeftFind == 'W')
            num++;
        if(    ImageDeal[Ysite+3].IsLeftFind == 'W' && ImageDeal[Ysite+2].IsLeftFind == 'W'
            && ImageDeal[Ysite+1].IsLeftFind == 'W' && ImageDeal[Ysite].IsLeftFind == 'T')
            break;
    }
        //鍑嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
    if (ImageFlag.image_element_rings_flag == 1 && num>10)
    {
        ImageFlag.image_element_rings_flag = 2;
    }
    if (ImageFlag.image_element_rings_flag == 2 && num<8)
    {
        ImageFlag.image_element_rings_flag = 5;
    }
        //閿熸枻鎷烽敓鏂ゆ嫹
    if(ImageFlag.image_element_rings_flag == 5 && /*num>15)*/ImageStatus.Right_Line>25)
    {
        ImageFlag.image_element_rings_flag = 6;
    }
        //閿熸枻鎷烽敓鏂ゆ嫹灏忓渾閿熸枻鎷�
    if(ImageFlag.image_element_rings_flag == 6 && ImageStatus.Right_Line<3)
    {
        ImageFlag.image_element_rings_flag = 7;
    }
        //閿熸枻鎷烽敓鏂ゆ嫹 閿熸枻鎷峰渾閿熸枻鎷烽敓鍙鎷�
    if (ImageFlag.ring_big_small == 1 && ImageFlag.image_element_rings_flag == 7)
    {
        Point_Ysite = 0;
        Point_Xsite = 0;
        for (int Ysite = 50; Ysite > ImageStatus.OFFLine + 3; Ysite--)
        {
            if (       ImageDeal[Ysite].RightBorder <= ImageDeal[Ysite + 2].RightBorder
                    && ImageDeal[Ysite].RightBorder <= ImageDeal[Ysite - 2].RightBorder
                    && ImageDeal[Ysite].RightBorder <= ImageDeal[Ysite + 1].RightBorder
                    && ImageDeal[Ysite].RightBorder <= ImageDeal[Ysite - 1].RightBorder
                    && ImageDeal[Ysite].RightBorder <= ImageDeal[Ysite + 3].RightBorder
                    && ImageDeal[Ysite].RightBorder <= ImageDeal[Ysite - 3].RightBorder
               )
            {
                Point_Xsite = ImageDeal[Ysite].RightBorder;
                Point_Ysite = Ysite;
                break;
            }
        }
        if (Point_Ysite > 10)
        {
            ImageFlag.image_element_rings_flag = 8;
        }
    }
    //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    if (ImageFlag.image_element_rings_flag == 8)
    {
        if (
                //Straight_Judge(2, ImageStatus.OFFLine+15, 50) < 1
                ImageStatus.Right_Line < 8     // 閿熸枻鎷烽敓鏂ゆ嫹閿熻妭浼欐嫹閿熸枻鎷烽敓缁撳伐閿熸枻鎷烽敓鐨嗗嚖鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎴掕ˉ鐩撮敓绔櫢鎷烽敓鐣岋紝閿熸枻鎷峰己閿熸枻鎷烽敓鏂ゆ嫹
                && ImageStatus.OFFLine < 13
                )    //閿熸彮鎲嬫嫹涓虹洿閿熸枻鎷烽敓鎻枻鎷锋閿熷彨锝忔嫹鍓嶇灮鍊奸敓鏂ゆ嫹閿熸枻鎷峰皬
        {
            ImageFlag.image_element_rings_flag = 9;
        }
    }
    //閿熸枻鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
    if (ImageFlag.image_element_rings_flag == 9)
    {
        int num=0;
        for (int Ysite = 45; Ysite > 8; Ysite--)
        {
            if(ImageDeal[Ysite].IsLeftFind == 'W' )
                num++;
        }
        if(num < 5)
        {
            ImageStatus.Road_type = 0;   //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓閾板嚖鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�0
            ImageFlag.image_element_rings_flag = 0;
            ImageFlag.image_element_rings = 0;
            ImageFlag.ring_big_small = 0;
        }
    }
    /***************************************閿熸枻鎷烽敓鏂ゆ嫹**************************************/
        //鍑嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
    if (   ImageFlag.image_element_rings_flag == 1
        || ImageFlag.image_element_rings_flag == 2
        || ImageFlag.image_element_rings_flag == 3
        || ImageFlag.image_element_rings_flag == 4)
    {
        for (int Ysite = 57; Ysite > ImageStatus.OFFLine; Ysite--)
        {
            ImageDeal[Ysite].Center = ImageDeal[Ysite].RightBorder - Half_Road_Wide[Ysite]-5;
        }
    }
        //閿熸枻鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鏂ゆ嫹
    if  ( ImageFlag.image_element_rings_flag == 5
        ||ImageFlag.image_element_rings_flag == 6
        )
    {
        int  flag_Xsite_1=0;
        int flag_Ysite_1=0;
        float Slope_Rings=0;
        for(Ysite=55;Ysite>ImageStatus.OFFLine;Ysite--)//閿熸枻鎷烽敓鑺ュ姬閿熸枻鎷�
        {
            for(Xsite=ImageDeal[Ysite].LeftBorder + 1;Xsite<ImageDeal[Ysite].RightBorder - 1;Xsite++)
            {
                if(  Pixle[Ysite][Xsite] == 1 && Pixle[Ysite][Xsite + 1] == 0)
                 {
                   flag_Ysite_1 = Ysite;
                   flag_Xsite_1 = Xsite;
                   Slope_Rings=(float)(79-flag_Xsite_1)/(float)(59-flag_Ysite_1);
                   break;
                 }
            }
            if(flag_Ysite_1 != 0)
            {
                break;
            }
        }
        if(flag_Ysite_1 == 0)
        {
            for(Ysite=ImageStatus.OFFLine+1;Ysite<30;Ysite++)
            {
                if(ImageDeal[Ysite].IsLeftFind=='T'&&ImageDeal[Ysite+1].IsLeftFind=='T'&&ImageDeal[Ysite+2].IsLeftFind=='W'
                    &&abs(ImageDeal[Ysite].LeftBorder-ImageDeal[Ysite+2].LeftBorder)>10
                  )
                {
                    flag_Ysite_1=Ysite;
                    flag_Xsite_1=ImageDeal[flag_Ysite_1].LeftBorder;
                    ImageStatus.OFFLine=Ysite;
                    Slope_Rings=(float)(79-flag_Xsite_1)/(float)(59-flag_Ysite_1);
                    break;
                }

            }
        }
        //閿熸枻鎷烽敓鏂ゆ嫹
        if(flag_Ysite_1 != 0)
        {
            for(Ysite=flag_Ysite_1;Ysite<60;Ysite++)
            {
                ImageDeal[Ysite].RightBorder=flag_Xsite_1+Slope_Rings*(Ysite-flag_Ysite_1);
                    ImageDeal[Ysite].Center = ((ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder)/2);
                if(ImageDeal[Ysite].Center<4)
                    ImageDeal[Ysite].Center = 4;
            }
            ImageDeal[flag_Ysite_1].RightBorder=flag_Xsite_1;
            for(Ysite=flag_Ysite_1-1;Ysite>10;Ysite--) //A閿熸枻鎷烽敓杈冨嚖鎷烽敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷�
            {
                for(Xsite=ImageDeal[Ysite+1].RightBorder-10;Xsite<ImageDeal[Ysite+1].RightBorder+2;Xsite++)
                {
                    if(Pixle[Ysite][Xsite]==1 && Pixle[Ysite][Xsite+1]==0)
                    {
                        ImageDeal[Ysite].RightBorder=Xsite;
                        ImageDeal[Ysite].Center = ((ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder)/2);
                        if(ImageDeal[Ysite].Center<4)
                            ImageDeal[Ysite].Center = 4;
                        ImageDeal[Ysite].Wide=ImageDeal[Ysite].RightBorder-ImageDeal[Ysite].LeftBorder;
                        break;
                    }
                }
                if(ImageDeal[Ysite].Wide>8 &&ImageDeal[Ysite].RightBorder< ImageDeal[Ysite+2].RightBorder)
                {
                    continue;
                }
                else
                {
                    ImageStatus.OFFLine=Ysite+2;
                    break;
                }
            }
        }
    }
    //閿熸枻鎷烽敓鑺傝鎷烽敓鏂ゆ嫹閿熸枻鎷�
    if (ImageFlag.image_element_rings_flag == 7){}
        //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹
    if (ImageFlag.image_element_rings_flag == 8 && ImageFlag.ring_big_small == 1)    //閿熸枻鎷峰渾閿熸枻鎷�
    {
        Repair_Point_Xsite = 20;
        Repair_Point_Ysite = 5;
        for (int Ysite = 40; Ysite > 5; Ysite--)
        {
            if (Pixle[Ysite][23] == 1 && Pixle[Ysite-1][23] == 0)//20
            {
                Repair_Point_Xsite =23;
                Repair_Point_Ysite= Ysite-1;
                ImageStatus.OFFLine = Ysite + 1;  //閿熸枻鎷锋閿熸枻鎷烽敓鏂ゆ嫹閿熼摪瑙勫垝
                break;
            }
        }
        for (int Ysite = 57; Ysite > Repair_Point_Ysite-3; Ysite--)//閿熸枻鎷烽敓鏂ゆ嫹
        {
            ImageDeal[Ysite].RightBorder = (ImageDeal[58].RightBorder - Repair_Point_Xsite) * (Ysite - 58) / (58 - Repair_Point_Ysite)  + ImageDeal[58].RightBorder;
           // ImageDeal[Ysite].RightBorder = ImageDeal[Ysite].LeftBorder + Half_Bend_Wide[Ysite];
            if(ImageDeal[Ysite].RightBorder>77){ImageDeal[Ysite].RightBorder = 77;}
            ImageDeal[Ysite].Center = ((ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2);
        }
    }
        //閿熺獤绛规嫹閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
    if (ImageFlag.image_element_rings_flag == 9 || ImageFlag.image_element_rings_flag == 10)
    {
        for (int Ysite = 59; Ysite > ImageStatus.OFFLine; Ysite--)
        {
            ImageDeal[Ysite].Center = ImageDeal[Ysite].RightBorder - Half_Road_Wide[Ysite];
        }
    }
}
//--------------------------------------------------------------
//  @name           Element_Handle_Right_Rings()
//  @brief          閿熸枻鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸帴鐚存嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�.
//  @parameter      void
//  @time
//  @Author         MRCHEN
//  Sample usage:   Element_Handle_Right_Rings();
//-------------------------------------------------------------
void Element_Handle_Right_Rings()
{
    /****************閿熸枻鎷烽敓鏂ゆ嫹*****************/
    int num =0 ;
    for (int Ysite = 55; Ysite > 30; Ysite--)
    {
        if(ImageDeal[Ysite].IsRightFind == 'W')
        {
            num++;
        }
        if(    ImageDeal[Ysite+3].IsRightFind == 'W' && ImageDeal[Ysite+2].IsRightFind == 'W'
            && ImageDeal[Ysite+1].IsRightFind == 'W' && ImageDeal[Ysite].IsRightFind == 'T' )
            break;
    }
        //鍑嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
    if (ImageFlag.image_element_rings_flag == 1 && num>10)
    {
        ImageFlag.image_element_rings_flag = 2;
    }
    if (ImageFlag.image_element_rings_flag == 2 && num<5)
    {
        ImageFlag.image_element_rings_flag = 5;
    }
        //閿熸枻鎷烽敓鏂ゆ嫹
    if(ImageFlag.image_element_rings_flag == 5 && ImageStatus.Left_Line>8)
    {
        ImageFlag.image_element_rings_flag = 6;
    }
        //閿熸枻鎷烽敓鏂ゆ嫹灏忓渾閿熸枻鎷�
    if(ImageFlag.image_element_rings_flag == 6 && ImageStatus.Left_Line<3)
    {
        ImageFlag.image_element_rings_flag = 7;
        //Stop=1;
    }
    if (ImageFlag.image_element_rings_flag == 7)
    {
        Point_Xsite = 0;
        Point_Ysite = 0;
        for (int Ysite = 50; Ysite > ImageStatus.OFFLine+3; Ysite--)
        {
            if (    ImageDeal[Ysite].LeftBorder >= ImageDeal[Ysite + 2].LeftBorder
                 && ImageDeal[Ysite].LeftBorder >= ImageDeal[Ysite - 2].LeftBorder
                 && ImageDeal[Ysite].LeftBorder >= ImageDeal[Ysite + 1].LeftBorder
                 && ImageDeal[Ysite].LeftBorder >= ImageDeal[Ysite - 1].LeftBorder
                 && ImageDeal[Ysite].LeftBorder >= ImageDeal[Ysite + 4].LeftBorder
                 && ImageDeal[Ysite].LeftBorder >= ImageDeal[Ysite - 4].LeftBorder
                )
            {
                Point_Xsite = ImageDeal[Ysite].LeftBorder;
                Point_Ysite = Ysite;
                break;
            }
        }
        if (Point_Ysite > 20)
        {
            ImageFlag.image_element_rings_flag = 8;
        }
        else if(ImageDeal[18].RightBoundary_First - ImageDeal[18].LeftBoundary_First>70)
        {
            ImageFlag.image_element_rings_flag = 8;
        }
    }
    if (ImageFlag.image_element_rings_flag == 8)
    {
         if (   //Straight_Judge(1, ImageStatus.OFFLine+10, 45) < 1
             /*&&*/ ImageStatus.Left_Line < 10 //閿熸枻鎷烽敓鏂ゆ嫹閿熻妭浼欐嫹閿熸枻鎷烽敓缁撳伐閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺殕锝忔嫹閿熸枻鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鐘舵€侀敓鏂ゆ嫹閿熺晫锛岄敓鏂ゆ嫹寮洪敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹绾﹂敓鏂ゆ嫹
             && ImageStatus.OFFLine < 16)    //閿熸彮鎲嬫嫹涓虹洿閿熸枻鎷烽敓鎻枻鎷锋閿熷彨锝忔嫹鍓嶇灮鍊奸敓鏂ゆ嫹閿熸枻鎷峰皬
            {ImageFlag.image_element_rings_flag = 9;}
    }
    if(ImageFlag.image_element_rings_flag == 9 )
    {
        int num=0;
        for (int Ysite = 45; Ysite > 10; Ysite--)
        {
            if(ImageDeal[Ysite].IsRightFind == 'W' )
            {
                num++;
            }
        }
        if(num < 5)
        {
            ImageStatus.Road_type = 0;   //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓閾板嚖鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�0
            ImageFlag.image_element_rings_flag = 0;
            ImageFlag.image_element_rings = 0;
            ImageFlag.ring_big_small = 0;
        }
    }
    /***************************************閿熸枻鎷烽敓鏂ゆ嫹**************************************/
         //鍑嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
    if (   ImageFlag.image_element_rings_flag == 1
        || ImageFlag.image_element_rings_flag == 2
        || ImageFlag.image_element_rings_flag == 3
        || ImageFlag.image_element_rings_flag == 4)
    {
        for (int Ysite = 59; Ysite > ImageStatus.OFFLine; Ysite--)
        {
            ImageDeal[Ysite].Center = ImageDeal[Ysite].LeftBorder + Half_Road_Wide[Ysite];
        }
    }
        //閿熸枻鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鏂ゆ嫹
    if (   ImageFlag.image_element_rings_flag == 5
        || ImageFlag.image_element_rings_flag == 6)
    {
        int flag_Xsite_1=0;
        int  flag_Ysite_1=0;
        float Slope_Right_Rings = 0;
        for(Ysite=55;Ysite>ImageStatus.OFFLine;Ysite--)
        {
            for(Xsite=ImageDeal[Ysite].LeftBorder + 1;Xsite<ImageDeal[Ysite].RightBorder - 1;Xsite++)
            {
                if(Pixle[Ysite][Xsite]==1 && Pixle[Ysite][Xsite+1]==0)
                {
                    flag_Ysite_1=Ysite;
                    flag_Xsite_1=Xsite;
                    Slope_Right_Rings=(float)(0-flag_Xsite_1)/(float)(59-flag_Ysite_1);
                    break;
                }
            }
            if(flag_Ysite_1!=0)
            {
              break;
            }
        }
        if(flag_Ysite_1==0)
        {
        for(Ysite=ImageStatus.OFFLine+5;Ysite<30;Ysite++)
        {
         if(ImageDeal[Ysite].IsRightFind=='T'&&ImageDeal[Ysite+1].IsRightFind=='T'&&ImageDeal[Ysite+2].IsRightFind=='W'
               &&abs(ImageDeal[Ysite].RightBorder-ImageDeal[Ysite+2].RightBorder)>10
         )
         {
             flag_Ysite_1=Ysite;
             flag_Xsite_1=ImageDeal[flag_Ysite_1].RightBorder;
             ImageStatus.OFFLine=Ysite;
             Slope_Right_Rings=(float)(0-flag_Xsite_1)/(float)(59-flag_Ysite_1);
             break;
         }
        }
        }
        //閿熸枻鎷烽敓鏂ゆ嫹
        if(flag_Ysite_1!=0)
        {
            for(Ysite=flag_Ysite_1;Ysite<58;Ysite++)
            {
                ImageDeal[Ysite].LeftBorder=flag_Xsite_1+Slope_Right_Rings*(Ysite-flag_Ysite_1);
                ImageDeal[Ysite].Center=(ImageDeal[Ysite].LeftBorder+ImageDeal[Ysite].RightBorder)/2;//閿熸枻鎷烽敓锟�
                if(ImageDeal[Ysite].Center>79)
                    ImageDeal[Ysite].Center=79;
            }
            ImageDeal[flag_Ysite_1].LeftBorder=flag_Xsite_1;
            for(Ysite=flag_Ysite_1-1;Ysite>10;Ysite--) //A閿熸枻鎷烽敓杈冨嚖鎷烽敓鏂ゆ嫹閿熸枻鎷锋壂閿熸枻鎷�
            {
                for(Xsite=ImageDeal[Ysite+1].LeftBorder+8;Xsite>ImageDeal[Ysite+1].LeftBorder-4;Xsite--)
                {
                    if(Pixle[Ysite][Xsite]==1 && Pixle[Ysite][Xsite-1]==0)
                    {
                     ImageDeal[Ysite].LeftBorder=Xsite;
                     ImageDeal[Ysite].Wide=ImageDeal[Ysite].RightBorder-ImageDeal[Ysite].LeftBorder;
                     ImageDeal[Ysite].Center=(ImageDeal[Ysite].LeftBorder+ImageDeal[Ysite].RightBorder)/2;//閿熸枻鎷烽敓锟�
                     if(ImageDeal[Ysite].Center>79)
                         ImageDeal[Ysite].Center=79;
                     if(ImageDeal[Ysite].Center<5)
                         ImageDeal[Ysite].Center=5;
                     break;
                    }
                }
                if(ImageDeal[Ysite].Wide>8 && ImageDeal[Ysite].LeftBorder>  ImageDeal[Ysite+2].LeftBorder)
                {
                    continue;
                }
                else
                {
                    ImageStatus.OFFLine=Ysite+2;
                    break;
                }
            }
        }
    }
        //閿熸枻鎷烽敓鑺傝鎷烽敓鏂ゆ嫹閿熸枻鎷�
    if (ImageFlag.image_element_rings_flag == 7){}
        //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹
    if (ImageFlag.image_element_rings_flag == 8)  //閿熸枻鎷峰渾閿熸枻鎷�
    {
        Repair_Point_Xsite = 39;
        Repair_Point_Ysite = 7;
        for (int Ysite = 40; Ysite > 5; Ysite--)
        {
            if (Pixle[Ysite][39] == 1 && Pixle[Ysite-1][39] == 0)
            {
                Repair_Point_Xsite = 39;
                Repair_Point_Ysite = Ysite-1;
                ImageStatus.OFFLine = Ysite + 1;  //閿熸枻鎷锋閿熸枻鎷烽敓鏂ゆ嫹閿熼摪瑙勫垝
                break;
            }
        }
        for (int Ysite = 57; Ysite > Repair_Point_Ysite-3; Ysite--)         //閿熸枻鎷烽敓鏂ゆ嫹
        {
            ImageDeal[Ysite].LeftBorder = (ImageDeal[58].LeftBorder - Repair_Point_Xsite) * (Ysite - 58) / (58 - Repair_Point_Ysite)  + ImageDeal[58].LeftBorder;
            //ImageDeal[Ysite].LeftBorder = ImageDeal[Ysite].RightBorder -  Half_Bend_Wide[Ysite]-11;
            if(ImageDeal[Ysite].LeftBorder<3){ImageDeal[Ysite].LeftBorder = 3;}
            ImageDeal[Ysite].Center = (ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2;
        }
    }
    //閿熺獤绛规嫹閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
    if (ImageFlag.image_element_rings_flag == 9)
    {
        for (int Ysite = 59; Ysite > ImageStatus.OFFLine; Ysite--)
        {
            ImageDeal[Ysite].Center = ImageDeal[Ysite].LeftBorder + Half_Road_Wide[Ysite];
        }
    }
}
//uint8 Pass_flag = 'F';
//int for_err = 0;
//int L_T_R_W;
//uint8 Circle_Off = 'F';  //閿熸埅鎲嬫嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷风姸鎬佷綅  閿熸枻鎷烽敓鏂ゆ嫹閿熺潾杈规拝鎷烽敓鏂ゆ嫹
//uint8 Out_Flag = 0;      //閿熻鍑ゆ嫹閿熸彮纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻纰夋嫹
//int circleoff_lenth;     //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨鎾呮嫹閿熸枻鎷�
//int circle_just_one=1;
//
//
////閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//void CircleTest() {
// // if(adcsum>4200)
//  if ( (adcsum >= 5000)/*||(adcleft>2000&&adcright<800)||(adcleft<800&&adcright>2000) */   //3800
//      &&ImageStatus.CirqueOut != 'T'
//      && ImageStatus.CirquePass != 'T'
//      &&ImageStatus.CirqueOff !='T')                              //閿熸枻鎷风朝閿熸枻鎷烽敓渚ョ鎷烽敓鏂ゆ嫹閿熻纰夋嫹閿熸枻鎷烽敓鐭紮鎷峰啓閿熸枻鎷烽敓鐨嗚鎷烽敓鏂ゆ嫹閿燂拷  閿熸枻鎷蜂箞閿熸枻鎷风嵕鐨嗚鎷烽敓锟�
//  {
//    ImageStatus.IsCinqueOutIn = 'T';                              //閿熷壙鎲嬫嫹蹇椾綅閿熸枻鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//  }
//
//  if (ImageStatus.IsCinqueOutIn == 'T')                           //閿熷彨璁规嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//  {
//    for (Ysite = 55; Ysite > (ImageStatus.OFFLine + 2); Ysite--)  //閿熸枻鎷峰渾閿熸枻鎷�
//    {
//      if ((ImageDeal[Ysite].LeftBorder + 8 < ImageDeal[Ysite - 2].LeftBorder)
//         &&ImageStatus.Road_type != RightCirque) {
//        ImageStatus.Road_type = LeftCirque;
//        Pass_flag = 'F';
//        break;
//      }
//      else if (( ImageDeal[Ysite].RightBorder - 8 >ImageDeal[Ysite - 2].RightBorder)
//               &&ImageStatus.Road_type != LeftCirque)               //閿熸枻鎷峰渾閿熸枻鎷�
//      {
//        ImageStatus.Road_type = RightCirque;
//        Pass_flag = 'F';
//        break;
//      }
//      Pass_flag ='T';
//                                                                    // 閿熺獤鎾呮嫹璇嗛敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹娌￠敓鏂ゆ嫹閿熸彮纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熸枻鎷烽敓鏂ゆ嫹鏃堕敓鏂ゆ嫹閿熺獤鎾呮嫹閿熸枻鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹閿熸枻鎷�
//                                                                    // 閿熸枻鎷烽敓鏂ゆ嫹閿熼叺鍖℃嫹閿熺殕鏀规唻鎷峰織浣嶉敓鏂ゆ嫹
//    }
//
//    if (Pass_flag == 'T')                                           //娌￠敓鏂ゆ嫹璇嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熸枻鎷烽敓绐栨拝鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//    {
//      if (ImageStatus.Cirque1lenth*OX > 140)                     // 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鑴氬彿纰夋嫹 璇撮敓鏂ゆ嫹閿熺獤鎾呮嫹閿熸枻鎷烽敓鏂ゆ嫹鍦嗛敓鏂ゆ嫹
//                                                                    // 閿熷彨纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹鑺敓鏂ゆ嫹鐗栧嚖鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸彮顏庢嫹鎱曢敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//      {
//        ImageStatus.CirquePass ='T';                                //閿熷壙鎲嬫嫹蹇楅敓鏂ゆ嫹绀洪敓绐栨拝鎷烽敓鏂ゆ嫹閿熻鍒板渾閿熸枻鎷烽敓鏂ゆ嫹  閫氶敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻鐤氳潡鈽呮嫹閿熸枻鎷风墫鍑ゆ嫹閿熸枻鎷烽敓锟�
//        ImageStatus.IsCinqueOutIn = 'F';
//        Pass_flag = 'F';                                            //閿熸枻鎷烽敓鏂ゆ嫹閿熻鐤氾拷
//      }
//    }
//  }
//
//  if (ImageStatus.CirquePass == 'T' &&ImageStatus.Pass_Lenth * OX > 50)    //閿熺獤鎾呮嫹閿熸枻鎷烽敓璇幆涔嬮敓鏂ゆ嫹閿熸彮顏庢嫹鍗搁摚閿熸枻鎷烽敓鏂ゆ嫹閿燂拷 //g5.22
//                                                                            //閿熸枻鎷锋病鍐� 閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹姊版偞浼欐嫹閿燂拷
//  {
//    if (ImageStatus.Road_type == RightCirque)                               //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//    {
//      for (Ysite = 53; Ysite > (ImageStatus.OFFLine + SystemData.OutCicle_line);Ysite--)  //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鍙╂厱閿燂拷  璇嗛敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹钄烽敓鏂ゆ嫹閿燂拷
//                                                                                          //閿熸枻鎷烽敓瑙掓枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹澶墠  閿熻緝鍗婇儴閿熻纰夋嫹鍥鹃敓鏂ゆ嫹閿熻鐚存嫹閿熸枻鎷�
//      {
//        if (((  ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite -10].LeftBorder >1)         //閿熷彨纭锋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨鈽呮嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
//             &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite +10].LeftBorder > 1))
//             ||(ImageDeal[Ysite + 1].IsLeftFind == 'T'
//              &&ImageDeal[Ysite].IsLeftFind == 'T'
//              &&ImageDeal[Ysite - 1].IsLeftFind == 'W')) {
//          ImageStatus.CirquePass = 'F';
//          ImageStatus.IsCinqueOutIn = 'F';
//          ImageStatus.CirqueOut = 'T';                                                    //璇嗛敓閲戝埌瑙掔鎷�  閿熸枻鎷锋椂鐘舵€侀敓鏂ゆ嫹娌欓敓鏂ゆ嫹閿熼樁鍒猴拷
//
//          break;
//        }
//      }
//    }
//
//    if (ImageStatus.Road_type == LeftCirque)                                              //g閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰悓閿熸枻鎷�  閿熸枻鎷峰渾閿熸枻鎷�
//    {
//      for (Ysite = 53; Ysite > (ImageStatus.OFFLine + SystemData.OutCicle_line);Ysite--)
//      {
//        if (((ImageDeal[Ysite -10].RightBorder - ImageDeal[Ysite].RightBorder >1)
//           &&(ImageDeal[Ysite +10].RightBorder - ImageDeal[Ysite].RightBorder >1))
//           ||(ImageDeal[Ysite + 1].IsRightFind == 'T'
//           && ImageDeal[Ysite].IsRightFind == 'T'
//           && ImageDeal[Ysite - 1].IsRightFind == 'W')) {
//              ImageStatus.CirquePass = 'F';
//              ImageStatus.IsCinqueOutIn = 'F';
//              ImageStatus.CirqueOut = 'T';
//
//          break;
//        }
//      }
//    }
//  }
//
//  if (ImageStatus.CirqueOut == 'T')                       //閿熻妭绛规嫹閿熸枻鎷烽敓鏂ゆ嫹鐘舵€�  閿熸枻鎷烽敓鍙鎷烽敓鏂ゆ嫹閿熶茎璇ф嫹閿熺杈炬嫹閿熸枻鎷�  閿熸枻鎷蜂篃瑕侀敓鍙鎷蜂粈涔堟椂閿熸枻鎷峰仠姝㈤敓鏂ゆ嫹閿熸枻鎷�
//                                                          //娌￠敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰憭閿熸枻鎷烽敓鏂ゆ嫹鍛涢敓鏂ゆ嫹閿燂拷  閿熸枻鎷蜂负鍥鹃敓鏂ゆ嫹閿熸枻鎷锋椂閿熸枻鎷烽敓鍙鎷烽敓锟�
//  {
//   if (ImageStatus.Cirque2lenth*OX>272 )          //   閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熼叺锛剁櫢鎷烽敓鏂ゆ嫹鍙╅敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
//                                                          // 閿熸枻鎷蜂箞閿熼叺鏂ゆ嫹閿熸枻鎷峰渾閿熸枻鎷�  閿熸枻鎷烽敓鏂ゆ嫹閿熸埅纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹鐘舵€�
// //      if((adcsum >= 2000)||(adcleft>2200&&adcright<700)||(adcleft<700&&adcright>2200))
//    {
//      ImageStatus.CirquePass = 'F';
//      ImageStatus.IsCinqueOutIn = 'F';
//      ImageStatus.CirqueOut = 'F';
//      ImageStatus.CirqueOff = 'T';                        //閿熷壙鎲嬫嫹蹇楅敓鏂ゆ嫹绀洪敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熸枻鎷蜂竴閿熻娇鎾呮嫹閿熸枻鎷烽敓鏂ゆ嫹閿熷彨璁规嫹閿熻鐜�  閿熸枻鎷锋閿熸枻鎷烽敓鏂ゆ嫹閿熻鐜�
//    }
//  }
//
//  if (ImageStatus.CirqueOff == 'T'
//      &&ImageStatus.Out_Lenth * OX >140)                 //閿熻妭鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷1-2m閿熸枻鎷烽敓鏂ゆ嫹閿熷彨鎲嬫嫹蹇椾綅閿熸枻鎷峰閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹姝㈤敓鏂ゆ嫹閿熻娇鏂ゆ嫹閿熸枻鎷�//150
//                                                          //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹OFF閿熸枻鎷峰織閿熸枻鎷烽敓锟� 閿熸埅纰夋嫹閿熺瓔寮€閿熸枻鎷风姸鎬�
//  {   ImageStatus.sanchaju = 1;
//      ImageStatus.CirquePass = 'F';
//      ImageStatus.IsCinqueOutIn = 'F';
//      ImageStatus.CirqueOut = 'F';
//      ImageStatus.CirqueOff = 'F';
//      ImageStatus.Road_type = 0;  //閿熸埅纰夋嫹鍘熼敓鏂ゆ嫹閿熸枻鎷风姸鎬�
//      circle_just_one=0;
//      SystemData.clrcle_num++;
//  }
//}
//
//static int Yjump1 = 0;
//int circle_r = 10;
//float circlk_k = 1.02;
//void Circle_Handle() {
//    //閿熻鐜敓鏂ゆ嫹閿熸枻鎷�
//  if (ImageStatus.IsCinqueOutIn == 'T')                           //閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹閿熻鐜姸鎬�
//  {
//    //閿熸枻鎷峰渾閿熸枻鎷�
//    if (ImageStatus.Road_type == LeftCirque) {
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine + 2; Ysite--)  //閿熸彮纰夋嫹閿熸枻鎷烽敓绔鎷�
//      {
//        if (ImageDeal[Ysite].LeftBorder + 8 < ImageDeal[Ysite - 2].LeftBorder) {
//          Yjump1 = Ysite;
//          ImageStatus.OFFLine = Yjump1;
//          break;
//        }
//      }
//
//      if (Yjump1 > 0) {                                           //閿熸枻鎷峰閿熸枻鎷烽敓鏂ゆ嫹
//        for (Ysite = Yjump1; Ysite < 55; Ysite++) {
//          int temp =ImageDeal[Yjump1].LeftBorder + circle_r * sqrt(Ysite - Yjump1);
//          if (temp < ImageDeal[Ysite].RightBorder)
//          {
//            ImageDeal[Ysite].RightBorder = temp;
//            if (Pixle[Ysite][ImageDeal[Ysite].RightBorder] == 0) {
//              for (Xsite = ImageDeal[Ysite].RightBorder;Xsite > ImageDeal[Ysite].LeftBorder; Xsite--) {
//                if (Pixle[Ysite][Xsite] == 1 && Pixle[Ysite][Xsite - 1] == 1) {
//                    ImageDeal[Ysite].RightBorder = Xsite;
//                }
//              }
//            }
//          }
//          ImageDeal[Ysite].Center =
//              (ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//        }
//      }
//    }
//
//    //閿熸枻鎷峰渾閿熸枻鎷�
//    if (ImageStatus.Road_type == RightCirque) {
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine + 2; Ysite--)  //閿熸彮纰夋嫹閿熸枻鎷烽敓绔鎷�
//      {
//        if (ImageDeal[Ysite].RightBorder - 8 >ImageDeal[Ysite - 2].RightBorder) {
//            Yjump1 = Ysite;
//            ImageStatus.OFFLine = Yjump1;
//            break;
//        }
//      }
//
//      if (Yjump1 > 0) {                                           //閿熸枻鎷峰閿熸枻鎷烽敓鏂ゆ嫹
//        for (Ysite = Yjump1; Ysite < 55; Ysite++) {
//          int temp =ImageDeal[Yjump1].RightBorder - circle_r * sqrt(Ysite - Yjump1);
//          if (temp > ImageDeal[Ysite].LeftBorder)
//          {
//            ImageDeal[Ysite].LeftBorder = temp;
//            if (Pixle[Ysite][ImageDeal[Ysite].LeftBorder] == 0) {
//              for (Xsite = ImageDeal[Ysite].LeftBorder;
//                   Xsite < ImageDeal[Ysite].RightBorder; Xsite++) {
//                if (Pixle[Ysite][Xsite] == 1 && Pixle[Ysite][Xsite + 1] == 1) {
//                  ImageDeal[Ysite].LeftBorder = Xsite;
//                }
//              }
//            }
//          }
//
//          ImageDeal[Ysite].Center =
//              (ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//        }
//      }
//    }
//  }
//
//  ////閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//
//  if (ImageStatus.CirqueOut == 'T')  //閿熸枻鎷锋椂閿熸枻鎷烽敓鑺傜鎷烽敓鏂ゆ嫹鐘舵€�
//  {
//    //閿熸枻鎷峰渾閿熸枻鎷�
//    float Det_R;
//    if (ImageStatus.Road_type == LeftCirque) {
//      Det_R = circlk_k * 79 / (55 - ImageStatus.OFFLine);                         //閿熸枻鎷烽敓濮愯ˉ閿熸枻鎷锋枩閿熸枻鎷�
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine; Ysite--) {
//        int temp = (int)(ImageDeal[55].RightBorder - Det_R * (55 - Ysite));
//        if (temp < 0) {
//          temp = 0;
//        }
//        if (temp < ImageDeal[Ysite].RightBorder) {                                //閿熸枻鎷烽敓鏂ゆ嫹
//          ImageDeal[Ysite].RightBorder = temp;
//          ImageDeal[Ysite].LeftBorder = 0;
//          ImageDeal[Ysite].Center =(ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//          ImageDeal[Ysite].Wide =ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;
//        }
//      }
//    }
////鍚岄敓鏂ゆ嫹
//    float Det_L;
//    if (ImageStatus.Road_type == RightCirque) {
//      Det_L = circlk_k * 79 / (55 - ImageStatus.OFFLine);
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine; Ysite--) {
//        int temp = (int)(ImageDeal[55].LeftBorder + Det_L * (55 - Ysite));
//        if (temp > 79) {
//          temp = 79;
//        }
//        if (temp > ImageDeal[Ysite].LeftBorder) {
//          ImageDeal[Ysite].LeftBorder = temp;
//          ImageDeal[Ysite].RightBorder = 79;
//          ImageDeal[Ysite].Center =
//              (ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//          ImageDeal[Ysite].Wide =
//              ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;
//        }
//      }
//    }
//  }
//}
//
//閿熸枻鎷烽敓鏂ゆ嫹閿熻妭纭锋嫹閿燂拷
uint8 f1 = 0;  //娌￠敓鏂ゆ嫹
uint8 f2 = 0;  //娌￠敓鏂ゆ嫹
uint8 f3 = 0;  //娌￠敓鏂ゆ嫹
uint8 Fork_in_1 = 0;//閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
uint8 Fork_in_2 = 0;//杩滈敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
uint8 Fork_in = 0;  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓琛楋拷
uint8 ForkLinePointx_l = 0;//閿熸枻鎷烽敓鑺ュ€掗敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
uint8 ForkLinePointx_r = 0;//閿熸枻鎷烽敓鑺ュ€掗敓鏂ゆ嫹閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹
int ForkLinePointy = 0;    //閿熸枻鎷烽敓鑺ュ€掗敓鏂ゆ嫹閿熻搴曟唻鎷烽敓鏂ゆ嫹
int Fork1_Y = 0;           //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
int Fork2_Y = 0;           //閿熸枻鎷烽敓鏂ゆ嫹杩滈敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
int Fork_dowm = 0;         //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷蜂喀閿熻锟�  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍓跨鎷�
//void ForkTest() {
//  int wide = 0;   //閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹
////  int Fork_thr;   //閿熷彨浼欐嫹寮洪敓鏂ゆ嫹閿熷彨鏂鎷烽敓鏂ゆ嫹鍊�
////  if (SystemData.Model < 2)
////    Fork_thr = 5000;
////  else
////    Fork_thr = 5000;
////     Fork_thr=5000;
//  //閿熸枻鎷烽敓鏂ゆ嫹鐩撮敓鏂ゆ嫹閿熸垝鍒伴敓鏂ゆ嫹閿熸枻鎷烽敓渚ョ鎷蜂竴閿熸枻鎷烽敓鏂ゆ嫹
// if (adcsum > 800)                 //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹
//  {
//    for (Ysite = 53; Ysite > (ImageStatus.OFFLine + 6);Ysite--)   //閿熸枻鎷锋Ysite閿熸枻鎷烽敓锟�
//
//    {
//      if ((  ImageDeal[Ysite].IsRightFind == 'T'
//           &&ImageDeal[Ysite + 1].IsRightFind == 'T')
//          ||(ImageDeal[Ysite].IsLeftFind == 'T'
//           &&ImageDeal[Ysite + 1].IsLeftFind =='T'))            //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓缁炴唻鎷烽敓鎻紮鎷烽敓缁撶湅閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�120*閿熸枻鎷峰渾閿熸枻鎷�
//      {
//        if (((ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite - 6].LeftBorder) >2
//             &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite - 6].LeftBorder) <8
//            &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite + 6].LeftBorder) >2
//             &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite + 6].LeftBorder) <8)        //閿熸枻鎷峰彥鎱曢敓锟�
//            ||((ImageDeal[Ysite - 6].RightBorder - ImageDeal[Ysite].RightBorder) >2
//             &&(ImageDeal[Ysite - 6].RightBorder - ImageDeal[Ysite].RightBorder) <8
//           // &&(ImageDeal[Ysite + 6].RightBorder - ImageDeal[Ysite].RightBorder) >2       //閿熸彮杈圭殑鏂ゆ嫹 閿熸枻鎷烽敓鏂ゆ嫹涓€閿熸枻鎷烽敓閰靛尅鎷烽敓鏂ゆ嫹  閿熸枻鎷蜂负閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹婕忛敓鏂ゆ嫹
//           //  &&(ImageDeal[Ysite + 6].RightBorder -ImageDeal[Ysite].RightBorder) < 8
//             ))     //閿熸枻鎷峰€奸敓鏂ゆ嫹瑕侀敓鏂ゆ嫹閿熸枻鎷�
//        {
//          Fork_in_1 = 'T';  //閿熸枻鎷风ず閿熸枻鎷烽敓鍓跨殑瑙掔鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎻鎷�
//          Fork1_Y = Ysite;  //閿熸枻鎷峰綍閿熸枻鎷蜂竴閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//          break;
//        }
//
//        else {
//          Fork_in_1 = 'F';  //娌￠敓鎻鎷稧G
//        }
//      }
//    }
//
//    //閿熻妭璁规嫹閿熸枻鎷烽敓鏂ゆ嫹  閿熸彮鐚存嫹鑹查敓鏂ゆ嫹閿熻鍖℃嫹  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷风帿閿熸枻鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹閿熸枻鎷锋伅
//    for (Ysite = Fork1_Y; Ysite > (ImageStatus.OFFLine);Ysite--)                                          //閿熸帴纰夋嫹涓€閿熸枻鎷烽敓鏂ゆ嫹閿熷寮€濮嬮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
//    {
//      PicTemp = Pixle[Ysite];
//      for (Xsite = ImageDeal[Ysite].LeftBorder; Xsite < 50;Xsite++)                                       //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熺即顐嫹閿熸枻鎷峰己閿燂拷
//      {
//        if ((*(PicTemp + Xsite) != 0) && (*(PicTemp + Xsite + 1) == 0) &&(*(PicTemp + Xsite + 2) == 0))   //閿熸彮纰夋嫹閿熸枻鎷疯壊閿熻鍖℃嫹閿熸枻鎷烽敓鏂ゆ嫹
//        {
//          ImageDeal[Ysite].Black_Wide_L = Xsite + 1;                                                       //閿熸枻鎷峰綍閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹璇掑憮閿燂拷
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_L =ImageDeal[Ysite].Center;                                          //娌￠敓鎻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷�
//      }
//
//      for (Xsite = ImageDeal[Ysite].RightBorder; Xsite > 30;Xsite--)                                       //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熺即顐嫹閿熸枻鎷峰己閿燂拷
//      {
//        if (  (*(PicTemp + Xsite) == 0)
//           && (*(PicTemp + Xsite - 1) == 0)
//            &&(*(PicTemp + Xsite + 1) != 0))      //閿熸彮纰夋嫹閿熸枻鎷疯壊閿熻鍖℃嫹閿熸枻鎷峰喍閿燂拷
//        {
//          ImageDeal[Ysite].Black_Wide_R = Xsite;  //閿熸枻鎷峰綍閿熸枻鎷锋椂閿熸枻鎷烽敓鎻粦杈规枻鎷�
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_R = ImageDeal[Ysite].Center;                                          //娌￠敓鎻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷�
//      }
//
//      for (Xsite = ImageDeal[Ysite].Black_Wide_L;
//           Xsite <= ImageDeal[Ysite].Black_Wide_R; Xsite++) {
//        if (ImageDeal[Ysite].Black_Wide_L == ImageDeal[Ysite].Center
//            ||ImageDeal[Ysite].Black_Wide_R ==ImageDeal[Ysite].Center)                                       //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋閿熻纰夋嫹閿熺煫纰怗閿熸枻鎷蜂负閿熸枻鎷烽敓鏂ゆ嫹娌￠敓鎻鎷�
//          break;
//        else if ((*(PicTemp + Xsite) == 0))     //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熸枻鎷锋恫閿熻顕嗘嫹閿熶茎榛戠鎷烽敓鏂ゆ嫹
//        {
//          wide++;                               //閿熸枻鎷烽敓鏂ゆ嫹閿熸彮纰夋嫹閿熸枻鎷烽敓瑙掑尅鎷疯皨閿熸枻鎷锋郴璇橀敓鏂ゆ嫹閿燂拷
//        }
//      }
//
//      ImageDeal[Ysite].BlackWide = wide;        //閿熸枻鎷峰綍閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//      ImageDeal[Ysite].Black_Pro =ImageDeal[Ysite].BlackWide / ImageDeal[Ysite].Wide;                         //鍥鹃敓鏂ゆ嫹璇橀敓鏂ゆ嫹閿熸枻鎷�
//      wide = 0;                                 //閿熸枻鎷�0
//    }
//
//    //閿熷彨璁规嫹閿熻鍑ゆ嫹涓洪敓鏂ゆ嫹閿熸枻鎷锋毊閿熺即顐嫹閿熸枻鎷峰己閿燂拷
//    for (Ysite = Fork1_Y; Ysite >= (ImageStatus.OFFLine + 1); Ysite--)  // g
//    {
//      if (( ImageDeal[Ysite].BlackWide - ImageDeal[Ysite + 3].BlackWide) >=2 //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹璇ら敓鏂ゆ嫹娑查敓琛楊噯鎷烽敓鑺傜鎷烽敓鏂ゆ嫹閿熼ズ杈冭鎷� 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻娇纰夋嫹閿熸枻鎷风姸
//          &&ImageDeal[Ysite].BlackWide > 21
//          &&ImageDeal[Ysite + 1].BlackWide > 17
//          &&ImageDeal[Ysite - 1].BlackWide > 17
//          &&(39 - ImageDeal[Ysite].Black_Wide_L) > 0                        //閿熷壙绛规嫹鏂滃崄閿熸枻鎷�
//          &&(ImageDeal[Ysite].Black_Wide_R - 39) > 0) {
//        ForkLinePointx_r = ImageDeal[Ysite].Black_Wide_R;                   //閿熸枻鎷烽敓鑺傝鎷烽敓绔殑纰夋嫹
//        ForkLinePointx_l = ImageDeal[Ysite].Black_Wide_L;
//        ForkLinePointy = Ysite;
//        Fork2_Y = Ysite;                                                    //閿熸枻鎷峰綍閿熻妭璁规嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//        if (Fork1_Y - Fork2_Y > 6)
//        {
//          Fork_in_2 ='T';                                                   //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�10   閿熸枻鎷烽敓鍙鎷蜂负閿熻鐜敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹  閿熸枻鎷烽敓鑺傚嚖鎷烽敓鏂ゆ嫹閿熸枻鎷�
//          break;
//        }
//
//      } else
//        Fork_in_2 = 'F';
//    }
//
//    if ((Fork_in_1 == 'T') && (Fork_in_2 == 'T'))
//      Fork_in = 'T';
//    else if ((Fork_in == 'T') && (Fork_in_2 == 'T'))
//      Fork_in = 'T';
//    else
//      Fork_in = 'F';
//
//    if (Fork_in == 'T')
//      ImageStatus.Road_type = Forkin;
//  }
//
////  閿熺獤鎾呮嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷   閿熸枻鎷烽敓閰靛垎鎲嬫嫹閿熸枻鎷峰€�  閿熸枻鎷烽敓鐭鎷疯瘑閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�   閿熼叺璇ф嫹閿熸枻鎷疯瘑閿熸枻鎷烽敓鎻紮鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
////  鍙璇嗛敓鏂ゆ嫹璇欓敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷 鍚岄敓鏂ゆ嫹
// else if (adcsum < 800)
//  {
//    //閿熻妭璁规嫹閿熸枻鎷烽敓鏂ゆ嫹  閿熸彮鐚存嫹鑹查敓鏂ゆ嫹閿熻鍖℃嫹  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷风帿閿熸枻鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹閿熸枻鎷锋伅
//    for (Ysite = 55; Ysite > (ImageStatus.OFFLine); Ysite--)
//    {
//      PicTemp = Pixle[Ysite];
//      for (Xsite = ImageDeal[Ysite].LeftBorder; Xsite < 55;Xsite++)  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熺即顐嫹閿熸枻鎷峰己閿燂拷
//      {
//        if ((  *(PicTemp + Xsite) != 0)
//            &&(*(PicTemp + Xsite + 1) == 0)
//            &&(*(PicTemp + Xsite + 2) == 0))                          //閿熸彮纰夋嫹閿熸枻鎷疯壊閿熻鍖℃嫹閿熸枻鎷烽敓锟�
//        {
//          ImageDeal[Ysite].Black_Wide_L = Xsite + 1;
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_L = ImageDeal[Ysite].Center;
//      }
//
//      for (Xsite = ImageDeal[Ysite].RightBorder; Xsite > 25;Xsite--)  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷疯閿熺即顐嫹閿熸枻鎷峰己閿燂拷//g
//      {
//        if ((   *(PicTemp + Xsite) == 0)
//             &&(*(PicTemp + Xsite - 1) == 0)
//             &&(*(PicTemp + Xsite + 1) != 0))                         //閿熸彮纰夋嫹閿熸枻鎷疯壊閿熻鍖℃嫹閿熸彮鎲嬫嫹
//        {
//          ImageDeal[Ysite].Black_Wide_R = Xsite;
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_R = ImageDeal[Ysite].Center;
//      }
//
//
//
//
//      for (Xsite = ImageDeal[Ysite].Black_Wide_L;Xsite <= ImageDeal[Ysite].Black_Wide_R; Xsite++) {
//        if (  ImageDeal[Ysite].Black_Wide_L == ImageDeal[Ysite].Center
//            ||ImageDeal[Ysite].Black_Wide_R == ImageDeal[Ysite].Center)
//          break;
//        else if ((*(PicTemp + Xsite) == 0)) {
//          wide++;
//        }
//      }
//
//      ImageDeal[Ysite].BlackWide = wide;
//      ImageDeal[Ysite].Black_Pro =ImageDeal[Ysite].BlackWide / ImageDeal[Ysite].Wide;  //鍥鹃敓鏂ゆ嫹璇橀敓鏂ゆ嫹閿熸枻鎷�
//      wide = 0;
//      if (ImageDeal[Ysite].BlackWide > 2)
//        ImageDeal[Ysite].isBlackFind = 'T';
//      else
//        ImageDeal[Ysite].isBlackFind = 'F';
//    }
//
//    //閿熷彨璁规嫹閿熻鍑ゆ嫹涓洪敓鏂ゆ嫹閿熸枻鎷锋毊閿熺即顐嫹閿熸枻鎷峰己閿燂拷
//    for (Ysite = 55; Ysite >= (ImageStatus.OFFLine); Ysite--)  // g
//    {
//      if (( ImageDeal[Ysite].BlackWide - ImageDeal[Ysite + 3].BlackWide) > 1
//          &&ImageDeal[Ysite].BlackWide > 16
//          &&ImageDeal[Ysite + 1].BlackWide > 15
//          && (39 - ImageDeal[Ysite].Black_Wide_L) > 0                                 //閿熷壙绛规嫹鏂滃崄閿熸枻鎷�
//          && (ImageDeal[Ysite].Black_Wide_R - 39) > 0) {
//        ForkLinePointx_r = ImageDeal[Ysite].Black_Wide_R;
//        ForkLinePointx_l = ImageDeal[Ysite].Black_Wide_L;
//        ForkLinePointy = Ysite;
//        Fork_in_2 = 'T';
//        break;
//      } else
//        Fork_in_2 = 'F';
//    }
//    if (Fork_in_2 == 'T')
//      Fork_in = 'T';
//    else
//      Fork_in = 'F';
//
//    f3 = Fork_in;
//    if (Fork_in == 'T') {
//      ImageStatus.Road_type = Forkout;
//    }
//  }
//
//  if (ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout)
//    Fork_dowm = 1;
//
//}
//
//void Fork_Handle() {
//  float Det_Fork_L;
//  float Det_Fork_R;
//  int yuansanshu;
//  yuansanshu=SystemData.clrcle_num%2;
//  if (  (ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout)
//      &&(yuansanshu == 1))                                           //閿熸枻鎷蜂竴鍦堥敓鎻鎷烽敓鏂ゆ嫹
//  {
//    Det_Fork_R = 0.7*(79 - ForkLinePointx_l) / (55 - ForkLinePointy);
//    for (Ysite = 55; Ysite > ImageStatus.OFFLine; Ysite--) {
//      int temp = (int)(ImageDeal[55].RightBorder - Det_Fork_R * (55 - Ysite));
//      if (temp < 0) {
//        temp = 0;
//      }
//      if (temp < ImageDeal[Ysite].RightBorder) {
//        ImageDeal[Ysite].RightBorder = temp;
//        if (Pixle[Ysite][ImageDeal[Ysite].RightBorder] == 0) {
//          for (Xsite = ImageDeal[Ysite].RightBorder;Xsite > ImageDeal[Ysite].LeftBorder; Xsite--) {
//            if (Pixle[Ysite][Xsite] == 1
//             && Pixle[Ysite][Xsite - 1] == 1) {
//              ImageDeal[Ysite].RightBorder = Xsite;
//            }
//          }
//        }
//      }
//      ImageDeal[Ysite].Center =(ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2;
//      ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //閿熸枻鎷烽敓楗洪潻鎷烽敓鏂ゆ嫹
//    }
//  }
//  if ((ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout) &&
//         ( yuansanshu == 0))   //閿熻妭璁规嫹鍦堥敓鏂ゆ嫹閿熸枻鎷�
//  {
//    Det_Fork_L = 1.05*ForkLinePointx_r / (55 - ForkLinePointy);
//    for (Ysite = 55; Ysite > ImageStatus.OFFLine; Ysite--) {
//      int temp = (int)(ImageDeal[55].LeftBorder + Det_Fork_L * (55 - Ysite));
//      if (temp > 79) {
//        temp = 79;
//      }
//      if (temp > ImageDeal[Ysite].LeftBorder) {
//        ImageDeal[Ysite].LeftBorder = temp;
//        if (Pixle[Ysite][ImageDeal[Ysite].LeftBorder] == 0) {
//          for (Xsite = ImageDeal[Ysite].LeftBorder;Xsite < ImageDeal[Ysite].RightBorder; Xsite++) {
//            if (Pixle[Ysite][Xsite] == 1 && Pixle[Ysite][Xsite + 1] == 1) {
//              ImageDeal[Ysite].LeftBorder = Xsite;
//            }
//          }
//        }
//      }
//      ImageDeal[Ysite].Center =(ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2;
//      ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //閿熸枻鎷烽敓楗洪潻鎷烽敓鏂ゆ嫹
//    }
//  }
//}



//void Fork_Handle2() {
// // float Det_Fork_L;
//  //float Det_Fork_R;
//  int yuansanshu;
//  yuansanshu=SystemData.clrcle_num%2;
//  if (  (ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout)
//      &&(yuansanshu == 1))                                           //閿熸枻鎷蜂竴鍦堥敓鎻鎷烽敓鏂ゆ嫹
//  {
//      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--) {
//      ImageDeal[Ysite].Center = ImageDeal[Ysite].LeftBorder + buxianwide[Ysite]*0.5;}
//      //ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //閿熸枻鎷烽敓楗洪潻鎷烽敓鏂ゆ嫹
//   //   Fit1(59,50);
//    }
//
//  if ((ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout) &&
//         ( yuansanshu == 0))   //閿熻妭璁规嫹鍦堥敓鏂ゆ嫹閿熸枻鎷�
//  {
//      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--) {
//      ImageDeal[Ysite].Center = ImageDeal[Ysite].RightBorder - buxianwide[Ysite]*0.5;}
//    //  Fit1(59,50);
//    }
//
//}
//
//
//
int ramp_flag = 1;
//extern int rukubz;
//extern int Sanchacha;
void Barn_test_in() {
  uint8 j = 0;

  for (Ysite = 30; Ysite < 55; Ysite++) {    // 閿熸枻鎷烽敓鑺傞潻鎷峰帇涔嬮敓鏂ゆ嫹閿熷姭搴︿紮鎷烽敓鏂ゆ嫹瑕侀敓鏂ゆ嫹纭敓鏂ゆ嫹閿熸枻鎷烽敓鐨嗗府鎷烽敓鏂ゆ嫹閿熺纰夋嫹鎵敓鏂ゆ嫹涓�30閿熸枻鎷�55 閿熸枻鎷锋閿熸枻鎷风‖閿熸枻鎷烽敓鍔害浼欐嫹閿熸枻鎷烽敓鏂ゆ嫹灏忛敓鏂ゆ嫹鐩撮敓鏂ゆ嫹鍒归敓鏂ゆ嫹閿熸枻鎷锋病閿熷彨鐧告嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    j = 0;
    for (Xsite = ImageDeal[Ysite].LeftBorder; Xsite < ImageDeal[Ysite].RightBorder; Xsite++) {
      if (Pixle[Ysite][Xsite] != Pixle[Ysite][Xsite + 1])  //閿熸枻鎷风嵕鏂ゆ嫹娉昏瘞閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
        j++;
    }
    if (j > 10 /*&&rampnum==2*/) {
      ImageStatus.Road_type = Barn_in;
  //    ramp_flag = 1;                                       //閿熸枻鎷风嵕鏂ゆ嫹閿熼叺甯嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻鐤氫紮鎷烽敓锟�1
 //     rampnum=0;
   //   barnlenth=SystemData.SpeedData.Length;
     // SystemData.clrcle_num = 0;
    //  circle_just_one=1;
   //   ++SystemData.rounds;
      break;
    }
  }

  if (  ImageStatus.Road_type == Barn_in
//      &&ImageStatus.Barn_Lenth * OX > 100
       && ImageStatus.Barn_Lenth >2000
      &&ImageStatus.Barn_Flag == 0)                         //閿熸枻鎷蜂竴閿熻娇纭锋嫹鐛炬枻鎷烽敓鏂ゆ嫹閿燂拷  閿熸枻鎷烽敓鏂ゆ嫹蹇椾綅閿熸枻鎷蜂负1
  {
      SystemData.Stop = 1;
      pwm_set_duty(ATOM1_CH4_P02_4,2000);
      pwm_set_duty(ATOM1_CH6_P02_6,2000);
//      ImageStatus.Road_type = 0;

 ///   SystemData.SpeedData.Length = 0;
  }
}
//
//
////閿熸枻鎷风崰鐧告嫹閿燂拷  閿熸枻鎷烽敓鐭紮鎷烽敓锟�
//static int Yjump4 = 0;
//void Barn_in_Handle(void) {
//  if (ImageStatus.Barn_Flag == 2) {
//    for (Ysite = 10; Ysite < 59; Ysite++) {
//      if ((ImageDeal[Ysite].close_RightBorder -
//           ImageDeal[Ysite - 2].close_RightBorder) > 5) {
//        Yjump4 = Ysite - 2;
//        break;
//      }
//    }
//    ImageStatus.OFFLine = Yjump4;
//    if (Yjump4 > 0) {
//      for (Ysite = Yjump4; Ysite < 55; Ysite++) {
//        int temp =
//            (int)(ImageDeal[Yjump4].close_RightBorder - (Ysite - Yjump4));
//        if (temp < 0)
//          temp = 0;
//        ImageDeal[Ysite].LeftBorder = temp;
//        ImageDeal[Ysite].RightBorder = 79;
//        ImageDeal[Ysite].Center =
//            (ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//      }
//    }
//  }
//}
//
////閿熸枻鎷烽敓瑙ｈˉ閿熸枻鎷�  閿熸枻鎷烽敓鐭紮鎷烽敓锟�
//void Barn_out_Handle(void) {
//  if (ImageStatus.Road_type == Barn_out) {
//    for (Ysite = 59; Ysite > ImageStatus.OFFLine; Ysite--) {
//      int temp = (int)(ImageDeal[59].LeftBorder + 1.2 * (59 - Ysite));
//      if (temp > 79)
//        temp = 79;
//
//      ImageDeal[Ysite].LeftBorder = temp;
//      ImageDeal[Ysite].RightBorder = 79;
//      ImageDeal[Ysite].Center =
//          (ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//    }
//  }
//}

//--------------------------------------------------------------
//  @name           straight_speed()
//  @brief          鐩撮敓绔》鎷烽敓鍔揪鎷烽敓鏂ゆ嫹
//  @parameter      void
//  @time
//  @Author         MRCHEN
//-------------------------------------------------------------
uint16 Speed_Goal_max=190;
uint16 Speed_Goal_min=170;
void straight_speed(void)
{
    if(ImageStatus.straight_acc == 1)               //鐩撮敓鏂ゆ嫹
        Speed_Goal = Speed_Goal_max;
    if(ImageStatus.straight_acc == 0)
        Speed_Goal = Speed_Goal_min;
    if(ImageStatus.Road_type == LeftCirque||ImageStatus.Road_type == RightCirque)
        Speed_Goal = Speed_Goal_min;
}

//閿熸枻鎷烽敓鑺傜》鎷烽敓鍔鎷风洿閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
float variance, variance_acc;  //閿熸枻鎷烽敓鏂ゆ嫹
void Straightacc_Test(void)
{
    int sum = 0;
    for (Ysite = 55; Ysite > ImageStatus.OFFLine + 1; Ysite--)
    {
        sum += (ImageDeal[Ysite].Center - ImageStatus.MiddleLine) *(ImageDeal[Ysite].Center - ImageStatus.MiddleLine);
    }
    variance_acc = (float)sum / (54 - ImageStatus.OFFLine);
    length_max = len_maxget();
    if(length_max > 52  //  閿熺瓔闀块敓鏂ゆ嫹閿熷彨锝忔嫹閫氶敓鏂ゆ嫹閿熷彨璁规嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓渚ュ尅鎷烽敓鏂ゆ嫹閿熻鍑ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹濞戭煉鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟� 閿熸枻鎷烽敓鍙鎷烽敓瑙掑嚖鎷蜂负鐩撮敓鏂ゆ嫹
    && ImageStatus.OFFLine <= 15 // 鐩撮敓鏂ゆ嫹閿熸枻鎷峰墠鐬讳竴閿熸枻鎷烽敓鏂ゆ嫹灏�
    && ImageStatus.Left_Line < 2  // 鐩撮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熻涓㈣竟纰夋嫹閿熸枻鎷烽敓锟�
    && ImageStatus.Right_Line < 2 //  && ImageStatus.Road_type == 0// 鐩撮敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸彮璁规嫹閿熺纰夋嫹閿熸枻鎷烽敓锟�
    && abs((ImageStatus.Det_True-39)) <6)
        ImageStatus.straight_acc = 1;
    else
        ImageStatus.straight_acc = 0;
}

//閿熸枻鎷烽敓鏂ゆ嫹涓€閿熷彨鐨勫府鎷烽敓鍙鎷烽敓鏂ゆ嫹
uint8 len(uint8 x)
{
    unsigned char line,y;
    for(line=55;line>0;line--)
    {
        if(!Pixle[line][x])
        {
            y=55-line;
            break;
        }
        else
            y=55;
    }
    return y;
}
//閿熸枻鎷烽敓鏂ゆ嫹20~60閿熸枻鎷蜂箣閿熸枻鎷烽敓鏂ゆ嫹鐣涖倧鎷烽敓鏂ゆ嫹璋愰敓鏂ゆ嫹閿燂拷
uint8 len_maxget(void)
{
    uint8 x,y,max=0;
    for(x=20;x<=60;x++)
    {
        y=len(x);
        if(max<y)
        {
            max=y;
        }
    }
    return max;
}

void Cross_Test2(){
    int leftlowlen=0;
    int leftmiddlen=0;
    int lefthighlen=0;
    int rightlowlen=0;
    int rightmiddlen=0;
    int righthighlen=0;
        //閿熸枻鎷烽敓鏂ゆ嫹閿熺粸顕嗘嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
    for (Ysite = 54; Ysite > ImageStatus.OFFLine+2; Ysite--) {

        //鍗侀敓琛楀簳杈圭鎷烽敓鍙唻鎷�
        if(ImageDeal[Ysite].IsLeftFind=='T'&&ImageDeal[Ysite-1].IsLeftFind=='T'&&leftlowlen==0){
            while(ImageDeal[Ysite].IsLeftFind=='T'){
                leftlowlen++;
                Ysite--;
                if(ImageDeal[Ysite].LeftBorder<ImageDeal[Ysite+5].LeftBorder-2){
                    leftlowlen=1;
                    break;
                }

            }
        }

        //鍗侀敓鏂ゆ嫹閿熷彨纭锋嫹浜╅敓鏂ゆ嫹閿燂拷
        if(ImageDeal[Ysite].IsLeftFind=='W'&&ImageDeal[Ysite-1].IsLeftFind=='W'&&leftmiddlen==0){
            while(ImageDeal[Ysite].IsLeftFind=='W'){
                leftmiddlen++;
                Ysite--;
            }
        }

        //鍗侀敓鏂ゆ嫹閿熻緝杈圭鎷烽敓鍙唻鎷�
        if(ImageDeal[Ysite].IsRightFind=='T'&&ImageDeal[Ysite-1].IsRightFind=='T'&&lefthighlen==0){
            while(ImageDeal[Ysite].IsRightFind=='T'){
                lefthighlen++;
                Ysite--;
            }
        }
    }
        //閿熸枻鎷烽敓鎻唻鎷峰崄閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
    for (Ysite = 54; Ysite > ImageStatus.OFFLine+2; Ysite--) {
        //鍗侀敓琛楀簳杈圭鎷烽敓鍙唻鎷�
        if(ImageDeal[Ysite].IsRightFind=='T'&&ImageDeal[Ysite-1].IsRightFind=='T'&&rightlowlen==0){
            while(ImageDeal[Ysite].IsRightFind=='T'){
                rightlowlen++;
                Ysite--;
                if(ImageDeal[Ysite].RightBorder>ImageDeal[Ysite+5].RightBorder+2){
                    rightlowlen=1;
                    break;
                }
            }
        }

        //鍗侀敓琛楀簳杈圭殑璁规嫹閿熸枻鎷�
        if(ImageDeal[Ysite].IsRightFind=='W'&&ImageDeal[Ysite-1].IsRightFind=='W'&&rightmiddlen==0){
            while(ImageDeal[Ysite].IsRightFind=='W'){
                rightmiddlen++;
                Ysite--;
            }
        }

        //鍗侀敓鏂ゆ嫹閿熻緝杈圭鎷烽敓鍙唻鎷�
        if(ImageDeal[Ysite].IsRightFind=='T'&&ImageDeal[Ysite-1].IsRightFind=='T'&&righthighlen==0){
            while(ImageDeal[Ysite].IsRightFind=='T'){
                righthighlen++;
                Ysite--;
            }
        }
    }
    if(     leftlowlen > 5 &&leftmiddlen > 5
          &&lefthighlen>4
          &&rightlowlen>5
          &&rightmiddlen>5
          &&righthighlen>4
          )
        ImageStatus.Road_type=Cross_ture;

//     if(ImageStatus.Cross_ture_lenth*OX>80)
//        ImageStatus.Road_type=0;
    // else
    //       Fork_dowm=0;


}

void Pcir_Handle() {
 // float Det_Fork_L;
  //float Det_Fork_R;

//  if (  (ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout))                                           //閿熸枻鎷蜂竴鍦堥敓鎻鎷烽敓鏂ゆ嫹
//  {
//      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--) {
//      ImageDeal[Ysite].Center = ImageDeal[Ysite].LeftBorder + buxianwide[Ysite]*0.5;}
//      //ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //閿熸枻鎷烽敓楗洪潻鎷烽敓鏂ゆ嫹
//   //   Fit1(59,50);
//    }

  if (ImageStatus.Road_type==Cross_ture)   //閿熻妭璁规嫹鍦堥敓鏂ゆ嫹閿熸枻鎷�
  {
      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--)
      {
      ImageDeal[Ysite].Center = ImageDeal[Ysite].RightBorder - buxianwide[Ysite]*0.5;
      ImageDeal[Ysite].LeftBorder=ImageDeal[Ysite].RightBorder - buxianwide[Ysite];
      }
      Fit1(59,50);
   }

}


/****鍏冮敓鎴》鎷烽敓锟�*****/  //鍦嗛敓鏂ゆ嫹 鍗侀敓鏂ゆ嫹 閿熸枻鎷烽敓鏂ゆ嫹 閿熸枻鎷疯閫氶敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鐨嗙》鎷烽敓鏂ゆ嫹閿熸枻鎷峰厓閿熸埅鎲嬫嫹蹇�  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰彧閿熸枻鎷蜂竴鐬敓鏂ゆ嫹
                     //閿熸枻鎷烽敓鏂ゆ嫹娌￠敓鏂ゆ嫹鐛炬枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓琛楁唻鎷峰摕鑸滈敓鏂ゆ嫹閿熸枻鎷烽敓锟�
uint8 Var_speed_start=0;//閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
uint8_t YH_flag=0;
void Element_Test(void)
{
    if(ImageStatus.Road_type != LeftCirque
     &&ImageStatus.Road_type != RightCirque)
    {
        ImageStatus.Road_type = 0;
        Straightacc_Test();
    }
    if(Var_speed_start==1)
    {
        straight_speed();//閿熷姭搴﹁揪鎷烽敓鏂ゆ嫹
    }
    //鍦嗛敓鏂ゆ嫹閿熸枻鎷烽敓锟�
//    if(ImageStatus.straight_acc == 0)//&& huan_start == 1)
//    {
        if(YH_flag == 0)
        {
            Element_Judgment_Left_Rings();           //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
            Element_Judgment_Right_Rings();          //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
        }
        else if(YH_flag == 1)
        {
            Element_Judgment_Left_Rings();           //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
        }
        else if(YH_flag == 2)
        {
            Element_Judgment_Right_Rings();          //閿熸枻鎷峰渾閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
        }
//    }
}

void Element_Handle(void)
{
  if (ImageFlag.image_element_rings == 1)
      Element_Handle_Left_Rings();
  else if(ImageFlag.image_element_rings == 2)
      Element_Handle_Right_Rings();
}

uint8 all_stop_car[] = "9";
//extern int Sanchacha;
//extern int rukubz;
/****閿熸枻鎷烽敓鐣屽閿熸枻鎷�********/
void Stop_Test(void)
{
    if(ImageStatus.Road_type == LeftCirque || ImageStatus.Road_type == RightCirque)
        return;
    if(ImageStatus.OFFLine >= 55)           //閿熸枻鎷烽敓鏂ゆ嫹閿熻剼鐚存嫹灏忛敓鏂ゆ嫹閿熸彮鍖℃嫹閿熸帴鎾呮嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺煫浼欐嫹鑺崊閿熺粸鎾呮嫹閿熸枻鎷烽敓锟�
        SystemData.Stop = 1;
}

void Stop_Test3()
{
    uint8 whitepoint = 0 ;
    for(uint8 i = 0; i < 80 ; i++)
    {

        if( Pixle[59][i] )
        {
            whitepoint ++;
            tft180_show_int(30,125,whitepoint,3);
            if(whitepoint  < whilepoint_protect)
            {
                Stop_car_Flag = 1;
            }
        }
    }

}

void DrawLine()  //閿熸枻鎷烽敓绔枻鎷�  閿熺煫纰夋嫹閿熸枻鎷�
{
  uint8 i;
  for (i = 59; i > ImageStatus.OFFLine; i--) {
    Pixle[i][ImageDeal[i].LeftBorder + 2] = 0;  //閿熺嫛璁规嫹閿熸枻鎷蜂綅閿熸枻鎷烽敓鑺傝璇ф嫹
    Pixle[i][ImageDeal[i].RightBorder - 2] = 0;
    Pixle[i][ImageDeal[i].Center] = 0;
  }
}

/*****************閿熸枻鎷风晭鎱堫煉鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�**********************/
void GetDet() {
  float DetTemp = 0;
  int TowPoint = 0;
  float SpeedGain = 0;
  float UnitAll = 0;

  SpeedGain=(SystemData.SpeedData.nowspeed - SystemData.SpeedData.MinSpeed) * 0.2 +0.5 ;//閿熸枻鎷烽敓鏂ゆ嫹閿熷姭搴︾鎷烽敓鏂ゆ嫹鍓嶇灮閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�   閿熷姭搴﹂潻鎷烽敓鏂ゆ嫹80  閿熸枻鎷烽敓鏂ゆ嫹涓洪敓鏂ゆ嫹閿熸枻鎷�  鍓嶇灮閿熸帴绛规嫹

    if (SpeedGain >= 3)
      SpeedGain = 3;
    else if (SpeedGain <= -1)
      SpeedGain = -1;

//    if ((ImageStatus.Road_type == RightCirque ||ImageStatus.Road_type == LeftCirque)&&ImageStatus.CirqueOff == 'F')
//    TowPoint = 23;                                                                      //鍦嗛敓鏂ゆ嫹鍓嶇灮

    else if (ImageStatus.Road_type == Straight)
    TowPoint = SystemData.straighet_towpoint;

  else if(ImageStatus.Road_type ==Cross_ture)
  {
      TowPoint=22;
  }
  else if(ImageStatus.Road_type == LeftCirque || ImageStatus.Road_type == RightCirque)
  {
      TowPoint=22;
  }
else
    TowPoint = ImageStatus.TowPoint-SpeedGain;                                          //閿熷姭璁规嫹瓒婇敓鏂ゆ嫹鍓嶇灮瓒婇敓鏂ゆ嫹

  if (TowPoint < ImageStatus.OFFLine)
    TowPoint = ImageStatus.OFFLine + 1;

  if (TowPoint >= 49)
    TowPoint = 49;

  if ((TowPoint - 5) >= ImageStatus.OFFLine) {                                          //鍓嶇灮鍙栭敓鍊熷畾鍓嶇灮閿熸枻鎷烽敓瑙掑尅鎷烽敓鎺ユ拝鎷烽敓鏂ゆ嫹  閿熸枻鎷疯閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
    for (int Ysite = (TowPoint - 5); Ysite < TowPoint; Ysite++) {
      DetTemp = DetTemp + Weighting[TowPoint - Ysite - 1] * (ImageDeal[Ysite].Center);
      UnitAll = UnitAll + Weighting[TowPoint - Ysite - 1];
    }
    for (Ysite = (TowPoint + 5); Ysite > TowPoint; Ysite--) {
      DetTemp += Weighting[-TowPoint + Ysite - 1] * (ImageDeal[Ysite].Center);
      UnitAll += Weighting[-TowPoint + Ysite - 1];
    }
    DetTemp = (ImageDeal[TowPoint].Center + DetTemp) / (UnitAll + 1);

  } else if (TowPoint > ImageStatus.OFFLine) {
    for (Ysite = ImageStatus.OFFLine; Ysite < TowPoint; Ysite++) {
      DetTemp += Weighting[TowPoint - Ysite - 1] * (ImageDeal[Ysite].Center);
      UnitAll += Weighting[TowPoint - Ysite - 1];
    }
    for (Ysite = (TowPoint + TowPoint - ImageStatus.OFFLine); Ysite > TowPoint;
         Ysite--) {
      DetTemp += Weighting[-TowPoint + Ysite - 1] * (ImageDeal[Ysite].Center);
      UnitAll += Weighting[-TowPoint + Ysite - 1];
    }
    DetTemp = (ImageDeal[Ysite].Center + DetTemp) / (UnitAll + 1);
  } else if (ImageStatus.OFFLine < 49) {
    for (Ysite = (ImageStatus.OFFLine + 3); Ysite > ImageStatus.OFFLine;
         Ysite--) {
      DetTemp += Weighting[-TowPoint + Ysite - 1] * (ImageDeal[Ysite].Center);
      UnitAll += Weighting[-TowPoint + Ysite - 1];
    }
    DetTemp = (ImageDeal[ImageStatus.OFFLine].Center + DetTemp) / (UnitAll + 1);

  } else
    DetTemp =ImageStatus.Det_True;                                                     //閿熸枻鎷烽敓鏂ゆ嫹娴呴敓鏂ゆ嫹閿熺祮FFLine>50閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎻紮鎷疯敋閿熺嫛顐嫹閿熻锟�

  ImageStatus.Det_True = DetTemp;                                                      //閿熸枻鎷锋椂閿熶茎鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鐙℃枻鎷烽敓閰电》鎷烽敓鐙☆偓鎷烽敓锟�
//  if()
  ImageStatus.TowPoint_True = TowPoint;                                                //閿熸枻鎷锋椂閿熸枻鎷峰墠鐬�
}


//--------------------------------------------------------------
//  @name           閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷�
//  @brief
//  @parameter      void
//-------------------------------------------------------------
int Zebras;   //閿熸枻鎷烽敓鏂ゆ嫹閿熺浼欐嫹閿熸枻鎷�
int Zebras_;    //閿熸枻鎷疯浆閿熸枻鎷烽敓鏂ゆ嫹
uint8  banmaxian_on=0;
void Element_Judgment_Zebra()//
{
    if( ImageStatus.Road_type == LeftCirque  //閿熸枻鎷锋閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰織浣嶆病閿熸帴纰夋嫹閿熸枻鎷蜂竴鐩村崰閿熺煫鎲嬫嫹蹇椾綅
      ||ImageStatus.Road_type == RightCirque
      ||banmaxian_on == 1) return;

    int NUM = 0,net = 0;
    banmaxian_on=0;

    for (int Ysite = 50; Ysite <55 ; Ysite++)          // 25   35
    {
        for (int Xsite =ImageDeal[Ysite].LeftBoundary-5 ; Xsite < ImageDeal[Ysite].RightBoundary+5; Xsite++)
        {
            if (Pixle[Ysite][Xsite] == 0 && Pixle[Ysite][Xsite + 1] == 1)
            {
                net++;
                if (net >8)
                {
                    NUM++;
                    break;
                }
            }
        }
        if(NUM>4)
        {
            banmaxian_on=1;
            break;
        }
    }
}

int sanchachazhi;
float Det = 0;
extern int cpu1_get_err;
void ImageProcess(void) {
    compressimage();          //鍥鹃敓鏂ゆ嫹鍘嬮敓鏂ゆ嫹 0.6ms
    ImageStatus.OFFLine = 2;  //閿熸枻鎷烽敓琛楃鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓缁炵鎷烽敓鏂ゆ嫹閿熺煫纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
    ImageStatus.WhiteLine = 0;
  for (Ysite = 59; Ysite >= ImageStatus.OFFLine; Ysite--) {
    ImageDeal[Ysite].IsLeftFind = 'F';
    ImageDeal[Ysite].IsRightFind = 'F';
    ImageDeal[Ysite].LeftBorder = 0;
    ImageDeal[Ysite].RightBorder = 79;
    ImageDeal[Ysite].LeftTemp = 0;
    ImageDeal[Ysite].RightTemp = 79;
//    ImageDeal[Ysite].Black_Wide_L = 39;
//    ImageDeal[Ysite].Black_Wide_R = 39;
//    ImageDeal[Ysite].BlackWide = 0;

    // g  5.12
    ImageDeal[Ysite].close_LeftBorder = 0;
    ImageDeal[Ysite].close_RightBorder = 79;
//    ImageDeal[Ysite].opp_LeftBorder = 0;
//    ImageDeal[Ysite].opp_RightBorder = 0;

  }                     //閿熺鏂ゆ嫹閿熸枻鎷烽敓琛楃枤浼欐嫹閿熺粸纭锋嫹閿燂拷

 // K = Fit1_k(59-ImageStatus.OFFLine+10,10);

  Get01change_dajin();  //鍥鹃敓鏂ゆ嫹閿熻纰夋嫹閿燂拷    2.7ms
  //tft180_show_string(0,90,"che");
  //if(SystemData.clrcle_num!=2)
  Pixle_Filter();     //閿熸枻鎷疯殌         1.7ms}

  DrawLinesFirst();     //閿熸枻鎷烽敓鐙″簳鎲嬫嫹      30us
  DrawLinesProcess();   //閿熺煫纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹  8us
  Search_Border_OTSU(Pixle, LCDH, LCDW, LCDH - 2);//58閿熸枻鎷蜂綅閿熸枻鎷烽敓鏂ゆ嫹

  /***鍏冮敓鏂ゆ嫹璇嗛敓鏂ゆ嫹*****/
  Element_Test();                   //5us
  /***鍏冮敓鏂ゆ嫹璇嗛敓鏂ゆ嫹*****/
  DrawExtensionLine();
  RouteFilter();        //閿熸枻鎷烽敓鏂ゆ嫹閿熷壙璇ф嫹骞抽敓鏂ゆ嫹 2us

  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
  if(Zebras<320)    //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷烽敓鏂ゆ嫹鏃�
      Zebras++;
      if(Zebras>300)
          if(ImageStatus.Road_type != LeftCirque
           &&ImageStatus.Road_type != RightCirque)
              Element_Judgment_Zebra();  //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鍙鎷�

  /***鍏冮敓鎴揪鎷烽敓鏂ゆ嫹*****/
  Element_Handle();  // 3us
  /***鍏冮敓鎴揪鎷烽敓鏂ゆ嫹*****/
  Stop_Test();           //閿熸枻鎷烽敓鐣屼繚閿熸枻鎷�   閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰嵈閿燂拷
  GetDet();               //閿熸枻鎷峰彇閿熸枻鎷锋€佸墠鐬�  閿熸枻鎷烽敓鎻》鎷烽敓鏂ゆ嫹鍥鹃敓鏂ゆ嫹鍋忛敓鏂ゆ嫹 3us

  //cpu1_get_err == 1;
     // Menu_key_set();

  //Stop_Test3();//2024閿熸枻鎷�3閿熸枻鎷�7閿熸枻鎷�03:07:31

//  ImageStatus.Foresight = ((((ImageDeal[ImageStatus.OFFLine + 1].Center) +
//                             (ImageDeal[ImageStatus.OFFLine + 2].Center) +
//                             (ImageDeal[ImageStatus.OFFLine + 3].Center)) /3) -40);
//
//  ImageStatus.Det_all = (ImageStatus.Foresight + 40) - ImageDeal[54].Center;
//  ImageStatus.Det_all_k =(float)(ImageStatus.Det_all) / (ImageStatus.OFFLine + 2 - 54) * 30;
//  ImageStatus.Foresight = abs(ImageStatus.Foresight);
}
