#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

#include "zf_common_headfile.h"

#define uLCDH 120                            //用于图像显示的图像高度
#define uLCDW 160                            //用于图像显示的图像宽度
#define LCDH 60
#define LCDW 80
#define HMAX (LCDH - 1)                      //没用
#define WMAX (LCDW - 1)                      //没用
#define LimitL(L) (L = ((L < 1) ? 1 : L))    //限制幅度
#define LimitH(H) (H = ((H > 78) ? 78 : H))  //限制幅度
#define ImageSensorMid 39                    //图像屏幕中点
extern int ImageScanInterval;  //扫边范围    上一行的边界+-ImageScanInterval
extern int ImageScanInterval_Cross;  //十字扫边范围
extern uint8 Image_Use[LCDH][LCDW];
extern uint8 Pixle[LCDH][LCDW];
extern uint8 UImage_Use[uLCDH][uLCDW];
extern float variance;  //方差
extern int ForkLinePointy;
extern float variance_acc;
extern int Fork_dowm;
extern int circle_r;
extern float circlk_k;
extern int circleoff_lenth;//
extern int forklenth;
extern int barnlenth;
extern int ramplenth;
extern int ramptestflag;
extern int rampnum;

#define whilepoint_protect 50
extern uint8 Stop_car_Flag;;

typedef struct {
  int point;
  uint8 type;
} JumpPointtypedef;

typedef struct {
  float nowspeed;     // pulse表示nowspeed
  int expectspeed;    // speed表示expectspeed
  int motor_duty;     //电机占空比
  float Length;       //走过路程
  int Circle_OUT_th;
  int MinSpeed;             //最低速度
  int MaxSpeed;             //最高速度
  float expect_True_speed;  //实际期望速度
  int straight_speed;       //直道速度
} SpeedDatatypedef;

typedef struct {
  /*左右边边界标志    T为正常跳变边    W为无边   P为障碍类多跳边的内边*/
  uint8 IsRightFind;      //右边有边标志
  uint8 IsLeftFind;       //左边有边标志
  uint8 isBlackFind;      //三叉边
  int Wide;               //边界宽度
  int LeftBorder;         //左边界
  int RightBorder;        //右边界
  int close_LeftBorder;   //靠边边界
  int close_RightBorder;  //靠边边界
  int opp_LeftBorder;     //反向边界
  int opp_RightBorder;    //反向边界
  int Center;             //中线
  int RightTemp;          //右边临时值
  int LeftTemp;           //左边临时值
  int CenterTemp;         //中线临时值
  int Black_Point;        //单行黑点数量

  //左右手法则扫线数据
  int LeftBoundary_First;  //左边界 保存第一次数据
  int RightBoundary_First; //右边界 保存第一次数据
  int LeftBoundary;        //左边界 保存最后一次数据
  int RightBoundary;       //右边界 保存最后一次数据

  // fork   下面的变量用于岔路口的检测
} ImageDealDatatypedef;


//元素类型
typedef enum {
  Normol,       //无任何特征
  Straight,     ////直道
  Cross,        ////十字
  Ramp,         //坡道
  LeftCirque,   ////左圆环
  RightCirque,  ////右圆环
  Forkin,       //岔路进口
  Forkout,      //岔路出口
  Barn_out,     //出库
  Barn_in,      //入库
  Cross_ture,
} RoadType_e;

typedef struct {
  /*以下关于全局图像正常参数*/

  //图像信息
  uint8 TowPoint;             //初始比较点           给定前瞻
  int TowPointAdjust_v;     //初始比较点适应速度    没用
  int TowPoint_True;        //实际比较点           没用
  int TowPoint_Gain;        //增益系数             没用
  int TowPoint_Offset_Max;  //最大偏置系数         没用
  int TowPoint_Offset_Min;  //最小偏置系数         没用
  int Det_True;             //由GetDet()函数解算出来的平均图像偏差
  int Det_all;              //图像的近端到远端的总偏差
  float Det_all_k;          //斜率

  uint8 Threshold;          //二值化阈值
  uint32 Threshold_static;  //二值化静态下限
  uint8 Threshold_detach;   //阳光算法分割阈值
  uint8 MiddleLine;         //屏幕中心
  int Foresight;            //偏差速度因子   远端的偏差  用于控速
  uint8 Left_Line;          //左边丢边数
  uint8 Right_Line;         //右边丢边数
  uint8 OFFLine;            /////图像顶边
  uint8 WhiteLine;          ////双边丢边数
  float ExpectCur;          /////图像期望曲率    没用
  float White_Ritio;        //有效行白点比例     没用
  int Black_Pro_ALL;        //整体黑点比例%      没用

  // PID
  float Piriod_P;  //分段P   值     没用
  float MU_P;

  RoadType_e Road_type;  //元素类型

  /****圆环***/
  uint8 IsCinqueOutIn;  //进出圆环
  uint8 CirquePass;     //圆环中
  uint8 CirqueOut;      //出圆环
  uint8 CirqueOff;      //圆环结束

  //左右手法则扫线数据

  int16 WhiteLine_L;        //左边丢线数
  int16 WhiteLine_R;        //右边丢线数
  int16 OFFLineBoundary;   //八领域截止行

  int Pass_Lenth;       //入环距离  用于防抖
                        /****圆环***/
  int Cirque1lenth;        //tly1
  int Cirque2lenth;        //tly2
  int Out_Lenth;     //
  int Fork_Out_Len;  //出岔口防抖
  int Dowm_lenth;    //三叉减速距离  //g5.13
  int Cross_Lenth;  // 270°转过之后一般是十字路口   作为三岔口的消抖
  int Cross_ture_lenth;
  int Sita;  //据此判断在过去一段路程中转过多少角度
  int pansancha_Lenth;

  //车库
  int Barn_Flag;   //判断库的次数
  int Barn_Lenth;  //入库停止距离
  int sanchaju;

  //保护
  int Stop_lenth;  //出界保护放误判距离
  //坡道减速
  int Ramp_lenth;

  int variance;  //直道检测阈值方差

  int straight_acc;  //直道加速标志位
  int  variance_acc;    //用于加速的阈值方差

  int ramptestlenth;//坡道检测间隔

  int rukuwait_lenth;
  int rukuwait_flag;
 // int Blue_lenth;
  int newblue_flag;

} ImageStatustypedef;

typedef struct{

  uint8 SteerOK;      //舵机启动标志
  uint8 CameraOK;     //摄像头启动显示标志
  uint8 OldCameraOK;  //灰度传输标志
  uint8 MotorOK;      //电机开关
  uint8 Point;        //赛道实际中心
  uint8 UpdataOK;     //数据更新
  uint8 Stop;         //停止标志
  uint8 GO_OK;        //冲冲冲
  int Model;          //车辆模式

  //图像参数
  int OutCicle_line;  //出环判断图像截止行  越大出环判断越严格越晚
  int L_T_R_W;  // 出环左有边右无边数量  越大出环结束越严格
  int Circleoff_offline;  //看到远处的距离判断出环结束  越小越严格
  int CircleP;            //环内P


//防误判距离
  int fork_start_lenth;  //岔路口检测起始
  int fork_off_lenth;//岔路口检测截止

  int circle_off_lenth;//出环防误判距离

  //小圆环
  int circles_pl;
  int circles_pr;
  int circles_off_lenth;//小圆环出环防误判距离

   //中圆环
  int circlem_pl;
  int circlem_pr;
  int circlem_off_lenth;//小圆环出环防误判距离

   //大圆环
  int circlel_pl;
  int circlel_pr;
  int circlel_off_lenth;//小圆环出环防误判距离
  int clrcle_priority[3];//圆环类型
  int clrcle_num;// 在第几个圆环


  int circle_kin;//入环补线半径
  float circle_kout;//出环补线斜率
  int circle_max_ang;//环内大叫限幅


  //直道
  float straight_p;//直道P
  float straight_d;//直道D
  int   straighet_towpoint;//直道前瞻


  int debug_lenth;//调试距离

  //摄像头配置
  int exp_time; //曝光时间
  int mtv_lroffset;//摄像头左右偏置
  int mtv_gain;//摄像头增益

  int ramp_lenth_start;//坡道距离
  int fork_lenth_start;//三叉距离
  int barn_lenth;//圆环距离

  int outbent_acc;//出弯加速


  int rounds; // 圈数
  int speed_per_round; // 每圈减速多少

  SpeedDatatypedef SpeedData;
} SystemDatatypdef;

typedef struct {
//    int16 Bend_Road;                            /*0 :无               1 :右弯道     2 :左弯道*/
    int16 image_element_rings;                  /*0 :无圆环          1 :左圆环       2 :右圆环*/
    int16 ring_big_small;                       /*0:无                     1 :大圆环       2 :小圆环*/
    int16 image_element_rings_flag;             /*圆环进程*/
    int16 straight_long;                        /*长直道标志位*/
//    int16 Garage_Location;                      /*0 :无车库          1 :左车库       2 :右车库*/
//    int16 Zebra_Flag;                           /*0 :无斑马线       1 左车库       2 :右车库*/
//    int16 Ramp;                                  /*0 :无坡道          1：坡道*/
//    int16 RoadBlock_Flag;                        /*0 :无路障            1 :路障*/
//    int16 Out_Road;                               /*0 :无断路      1 :断路*/
} ImageFlagtypedef;
void camera_display(void);  //图像显示
void compressimage();       ////压缩图像
void Get01change();         ////二值化图像
void Pixle_Filter();        ////像素滤波，效果不大
void Draw_Road(void);       ///绘制赛道边界
void ImageProcess(void);    ////图像处理主函数
void uncompressimage();     //图像解压
//void ForkTest();            //岔路口检测
void Cross_Test();          //圆环检测
void Cross_Handle();        //圆环处理
void Element_Test();        //元素检测
void Ramp_Test();           //坡道检测
void Barn_test_in();        //入库检测
float Straight_Judge_two(uint8 flag);
void Element_Handle();      //元素处理
uint8 len(uint8 x);         //计算一列长度
uint8 len_maxget(void);     //计算20-60列长度
//void Fork_Handle();         //三叉处理
//void Barn_in_Handle();      //没用
//void GetLenSita();          //没用了
//void Pcir_Handle(void);
int Limit(int num, int numH, int numL);
extern ImageStatustypedef ImageStatus;                //图像的全局变量
extern SystemDatatypdef SystemData;
extern uint8 length_max;
extern ImageDealDatatypedef ImageDeal[60];                //记录单行的信息
extern ImageFlagtypedef ImageFlag;
extern ImageStatustypedef ImageData;             ///////需要修改的图像阈值参数
extern uint16 exposure_time_self;

extern uint8  banmaxian_on;

extern uint8 Var_speed_start;//缓冲起步相关
extern uint16 Speed_Goal_max;
extern uint16 Speed_Goal_min;

#endif
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
  mt9v03x_finish_flag = 0;  //使用完一帧DMA传输的图像图像  可以开始传输下一帧
}


int HD_thre;  //临时观测变量
//二值化
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
          (thre))  //数值越大，显示的内容越多，较浅的图像也能显示出来
        Pixle[i][j] = 1;  //白
      else
        Pixle[i][j] = 0;  //黑
    }
  }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      优化的大津法
//  @param      image  图像数组
//  @param      clo    宽
//  @param      row    高
//  @param      pixel_threshold 阈值分离
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
  uint8* data = image;  //指向像素数据的指针
  for (i = 0; i < GrayScale; i++) {
    pixelCount[i] = 0;
    pixelPro[i] = 0;
  }

  uint32 gray_sum = 0;
  //统计灰度级中每个像素在整幅图像中的个数
  for (i = 0; i < height; i += 1) {
    for (j = 0; j < width; j += 1) {
      // if((sun_mode&&data[i*width+j]<pixel_threshold)||(!sun_mode))
      //{
      pixelCount[(
          int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
      gray_sum += (int)data[i * width + j];  //灰度值总和
      //}
    }
  }

  //计算每个像素值的点在整幅图像中的比例
  for (i = 0; i < GrayScale; i++) {
    pixelPro[i] = (float)pixelCount[i] / pixelSum;
  }


  //遍历灰度级[0,255]
  float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
  w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
  for (j = 0; j < pixel_threshold; j++) {
    w0 +=
        pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和 即背景部分的比例
    u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

    w1 = 1 - w0;
    u1tmp = gray_sum / pixelSum - u0tmp;

    u0 = u0tmp / w0;    //背景平均灰度
    u1 = u1tmp / w1;    //前景平均灰度
    u = u0tmp + u1tmp;  //全局平均灰度
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

      if (Image_Use[i][j] >(thre))         //数值越大，显示的内容越多，较浅的图像也能显示出来
        Pixle[i][j] = 1;  //白
      else
        Pixle[i][j] = 0;  //黑
    }
  }
}


//像素滤波
void Pixle_Filter() {
  int nr;  //行
  int nc;  //列

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

// 01解压图像
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
////灰度解压图像
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


void GetJumpPointFromDet(uint8* p,uint8 type,int L,int H,JumpPointtypedef* Q)  //第一个参数是要查找的数组（80个点）
                                                                               //第二个扫左边线还是扫右边线
{                                                                              //三四是开始和结束点
  int i = 0;
  if (type == 'L')                              //扫描左边线
  {
    for (i = H; i >= L; i--) {
      if (*(p + i) == 1 && *(p + i - 1) != 1)   //由黑变白
      {
        Q->point = i;                           //记录左边线
        Q->type = 'T';                          //正确跳变
        break;
      } else if (i == (L + 1))                  //若果扫到最后也没找到
      {
        if (*(p + (L + H) / 2) != 0)            //如果中间是白的
        {
          Q->point = (L + H) / 2;               //认为左边线是中点
          Q->type = 'W';                        //非正确跳变且中间为白，认为没有边
          break;
        } else                                  //非正确跳变且中间为黑
        {
          Q->point = H;                         //如果中间是黑的
          Q->type = 'H';                        //左边线直接最大值，认为是大跳变
          break;
        }
      }
    }
  } else if (type == 'R')                       //扫描右边线
  {
    for (i = L; i <= H; i++)                    //从右往左扫
    {
      if (*(p + i) == 1 && *(p + i + 1) != 1)   //找由黑到白的跳变
      {
        Q->point = i;                           //记录
        Q->type = 'T';
        break;
      } else if (i == (H - 1))                  //若果扫到最后也没找到
      {
        if (*(p + (L + H) / 2) != 0)            //如果中间是白的
        {
          Q->point = (L + H) / 2;               //右边线是中点
          Q->type = 'W';
          break;
        } else                                  //如果中点是黑的
        {
          Q->point = L;                         //左边线直接最大值
          Q->type = 'H';
          break;
        }
      }
    }
  }
}





static uint8 DrawLinesFirst(void) {
  PicTemp = Pixle[59];                                     //原本59  改成了57
  if (*(PicTemp + ImageSensorMid) == 0)                 //如果底边图像中点为黑，异常情况
  {
    for (Xsite = 0; Xsite < ImageSensorMid; Xsite++)    //找左右边线
    {
      if (*(PicTemp + ImageSensorMid - Xsite) != 0)     //一旦找到左或右赛道到中心距离，就break
        break;                                          //并且记录Xsite
      if (*(PicTemp + ImageSensorMid + Xsite) != 0)
        break;
    }

    if (*(PicTemp + ImageSensorMid - Xsite) != 0)       //赛道如果在左边的话
    {
      BottomBorderRight = ImageSensorMid - Xsite + 1;   // 59行右边线有啦
      for (Xsite = BottomBorderRight; Xsite > 0; Xsite--)  //开始找59行左边线
      {
        if (*(PicTemp + Xsite) == 0 &&
            *(PicTemp + Xsite - 1) == 0)                //连续两个黑点，滤波
        {
          BottomBorderLeft = Xsite;                     //左边线找到
          break;
        } else if (Xsite == 1) {
          BottomBorderLeft = 0;                         //搜索到最后了，看不到左边线，左边线认为是0
          break;
        }
      }
    } else if (*(PicTemp + ImageSensorMid + Xsite) != 0)  //赛道如果在右边的话
    {
      BottomBorderLeft = ImageSensorMid + Xsite - 1;    // 59行左边线有啦
      for (Xsite = BottomBorderLeft; Xsite < 79; Xsite++)  //开始找59行左边线
      {
        if (  *(PicTemp + Xsite) == 0
            &&*(PicTemp + Xsite + 1) == 0)              //连续两个黑点，滤波
        {
          BottomBorderRight = Xsite;                    //右边线找到
          break;
        } else if (Xsite == 78) {
          BottomBorderRight = 79;                       //搜索到最后了，看不到右边线，左边线认为是79
          break;
        }
      }
    }
  }
  else                                                //左边线中点是白的，比较正常的情况
  {
    for (Xsite = 79; Xsite >ImageSensorMid; Xsite--)   //一个点一个点地搜索右边线
    {
      if (  *(PicTemp + Xsite) == 1
          &&*(PicTemp + Xsite - 1) == 1)                //连续两个黑点，滤波     //两个白点
      {
        BottomBorderRight = Xsite;                      //找到就记录
        break;
      } else if (Xsite == 40) {
        BottomBorderRight = 39;                         //找不到认为79
        break;
      }
    }
    for (Xsite = 0; Xsite < ImageSensorMid; Xsite++)    //一个点一个点地搜索左边线
    {
      if (  *(PicTemp + Xsite) == 1
          &&*(PicTemp + Xsite + 1) == 1)                //连续两个黑点，滤波
      {
        BottomBorderLeft = Xsite;                       //找到就记录
        break;
      } else if (Xsite == 38) {
        BottomBorderLeft = 39;                           //找不到认为0
        break;
      }
    }
  }
  BottomCenter =(BottomBorderLeft + BottomBorderRight) / 2;   // 59行中点直接取平均
  ImageDeal[59].LeftBorder = BottomBorderLeft;                //在数组里面记录一下信息，第一行特殊一点而已
  ImageDeal[59].RightBorder = BottomBorderRight;
  ImageDeal[59].Center = BottomCenter;                        //确定最底边
  ImageDeal[59].Wide = BottomBorderRight - BottomBorderLeft;  //存储宽度信息
  ImageDeal[59].IsLeftFind = 'T';
  ImageDeal[59].IsRightFind = 'T';
  for (Ysite = 58; Ysite > 54; Ysite--)                       //由中间向两边确定底边五行
  {
    PicTemp = Pixle[Ysite];
    for (Xsite = 79; Xsite > ImageDeal[Ysite + 1].Center;Xsite--)                                             //和前面一样的搜索
    {
      if (*(PicTemp + Xsite) == 1 && *(PicTemp + Xsite - 1) == 1) {
        ImageDeal[Ysite].RightBorder = Xsite;
        break;
      } else if (Xsite == (ImageDeal[Ysite + 1].Center+1)) {
        ImageDeal[Ysite].RightBorder = ImageDeal[Ysite + 1].Center;
        break;
      }
    }
    for (Xsite = 0; Xsite < ImageDeal[Ysite + 1].Center;Xsite++)                                             //和前面一样的搜索
    {
      if (*(PicTemp + Xsite) == 1 && *(PicTemp + Xsite + 1) == 1) {
        ImageDeal[Ysite].LeftBorder = Xsite;
        break;
      } else if (Xsite == (ImageDeal[Ysite + 1].Center-1)) {
        ImageDeal[Ysite].LeftBorder = ImageDeal[Ysite + 1].Center;
        break;
      }
    }
    ImageDeal[Ysite].IsLeftFind = 'T';                        //这些信息存储到数组里
    ImageDeal[Ysite].IsRightFind = 'T';
    ImageDeal[Ysite].Center =
        (ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) /2; //存储中点
    ImageDeal[Ysite].Wide =
        ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;      //存储宽度
  }
  return 'T';
}                                                             //最基本的要求，最近的五行首先不会受到干扰，这需要在安装的时候调整摄像头的视角

/*边线追逐大致得到全部边线*/
static void DrawLinesProcess(void)  //////不用更改
{
  uint8 L_Found_T = 'F';  //确定无边斜率的基准有边行是否被找到的标志
  uint8 Get_L_line = 'F';  //找到这一帧图像的基准左斜率
  uint8 R_Found_T = 'F';  //确定无边斜率的基准有边行是否被找到的标志
  uint8 Get_R_line = 'F';  //找到这一帧图像的基准右斜率
  float D_L = 0;           //延长线左边线斜率
  float D_R = 0;           //延长线右边线斜率
  int ytemp_W_L;           //记住首次左丢边行
  int ytemp_W_R;           //记住首次右丢边行
  ExtenRFlag = 0;          //标志位清0
  ExtenLFlag = 0;
   ImageStatus.Left_Line = 0;
   ImageStatus.WhiteLine = 0;
   ImageStatus.Right_Line = 0;
  for (Ysite = 54 ; Ysite > ImageStatus.OFFLine; Ysite--)            //前5行处理过了，下面从55行到（设定的不处理的行OFFLine）
  {                        //太远的图像不稳定，OFFLine以后的不处理
    PicTemp = Pixle[Ysite];
    JumpPointtypedef JumpPoint[2];                                          // 0左1右
    if (ImageStatus.Road_type != Cross_ture
           /* &&SystemData.SpeedData.Length*OX>500*/) {
      IntervalLow =ImageDeal[Ysite + 1].RightBorder -ImageScanInterval;             //从上一行右边线-Interval的点开始（确定扫描开始点）
      IntervalHigh =ImageDeal[Ysite + 1].RightBorder + ImageScanInterval;           //到上一行右边线+Interval的点结束（确定扫描结束点）
    } else {
      IntervalLow =ImageDeal[Ysite + 1].RightBorder -ImageScanInterval_Cross;       //从上一行右边线-Interval_Cross的点开始（确定扫描开始点）
      IntervalHigh = ImageDeal[Ysite + 1].RightBorder + ImageScanInterval_Cross;    //到上一行右边线+Interval_Cross的点开始（确定扫描开始点）
    }

    LimitL(IntervalLow);   //确定左扫描区间并进行限制
    LimitH(IntervalHigh);  //确定右扫描区间并进行限制
    GetJumpPointFromDet(PicTemp, 'R', IntervalLow, IntervalHigh,&JumpPoint[1]);     //扫右边线

    IntervalLow =ImageDeal[Ysite + 1].LeftBorder -ImageScanInterval;                //从上一行左边线-5的点开始（确定扫描开始点）
    IntervalHigh =ImageDeal[Ysite + 1].LeftBorder +ImageScanInterval;               //到上一行左边线+5的点结束（确定扫描结束点）

    LimitL(IntervalLow);   //确定左扫描区间并进行限制
    LimitH(IntervalHigh);  //确定右扫描区间并进行限制
    GetJumpPointFromDet(PicTemp, 'L', IntervalLow, IntervalHigh,&JumpPoint[0]);

    if (JumpPoint[0].type =='W')                                                    //如果本行左边线不正常跳变，即这10个点都是白的
    {
      ImageDeal[Ysite].LeftBorder =ImageDeal[Ysite + 1].LeftBorder;                 //本行左边线用上一行的数值
    } else                                                                          //左边线正常
    {
      ImageDeal[Ysite].LeftBorder = JumpPoint[0].point;                             //记录下来啦
    }

    if (JumpPoint[1].type == 'W')                                                   //如果本行右边线不正常跳变
    {
      ImageDeal[Ysite].RightBorder =ImageDeal[Ysite + 1].RightBorder;               //本行右边线用上一行的数值
    } else                                                                          //右边线正常
    {
      ImageDeal[Ysite].RightBorder = JumpPoint[1].point;                            //记录下来啦
    }

    ImageDeal[Ysite].IsLeftFind =JumpPoint[0].type;                                 //记录本行是否找到边线，即边线类型
    ImageDeal[Ysite].IsRightFind = JumpPoint[1].type;

    //重新确定那些大跳变的边缘
    if (( ImageDeal[Ysite].IsLeftFind == 'H'
         ||ImageDeal[Ysite].IsRightFind == 'H')) {
      if (ImageDeal[Ysite].IsLeftFind == 'H')                                   //如果左边线大跳变
        for (Xsite = (ImageDeal[Ysite].LeftBorder + 1);
             Xsite <= (ImageDeal[Ysite].RightBorder - 1);
             Xsite++)                                                           //左右边线之间重新扫描
        {
          if ((*(PicTemp + Xsite) == 0) && (*(PicTemp + Xsite + 1) != 0)) {
            ImageDeal[Ysite].LeftBorder =Xsite;                                 //如果上一行左边线的右边有黑白跳变则为绝对边线直接取出
            ImageDeal[Ysite].IsLeftFind = 'T';
            break;
          } else if (*(PicTemp + Xsite) != 0)                                   //一旦出现白点则直接跳出
            break;
          else if (Xsite ==(ImageDeal[Ysite].RightBorder - 1))
          {
             ImageDeal[Ysite].IsLeftFind = 'T';
            break;
          }
        }
      if ((ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder) <=
          7)                              //图像宽度限定
      {
        ImageStatus.OFFLine = Ysite + 1;  //如果这行比7小了后面直接不要了
        break;
      }
      if (ImageDeal[Ysite].IsRightFind == 'H')
        for (Xsite = (ImageDeal[Ysite].RightBorder - 1);
             Xsite >= (ImageDeal[Ysite].LeftBorder + 1); Xsite--) {
          if ((*(PicTemp + Xsite) == 0) && (*(PicTemp + Xsite - 1) != 0)) {
            ImageDeal[Ysite].RightBorder =
                Xsite;                    //如果右边线的左边还有黑白跳变则为绝对边线直接取出
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

 /***********重新确定无边行************/
    int ysite = 0;
    uint8 L_found_point = 0;
    uint8 R_found_point = 0;


    if(  ImageStatus.Road_type != Ramp)
    {
    if (    ImageDeal[Ysite].IsRightFind == 'W'
          &&Ysite > 10
          &&Ysite < 50
          &&ImageStatus.Road_type!=Barn_in
          )                     //最早出现的无边行
    {
      if (Get_R_line == 'F')    //这一帧图像没有跑过这个找基准线的代码段才运行
      {
        Get_R_line = 'T';       //找了  一帧图像只跑一次 置为T
        ytemp_W_R = Ysite + 2;
        for (ysite = Ysite + 1; ysite < Ysite + 15; ysite++) {
          if (ImageDeal[ysite].IsRightFind =='T')  //往无边行下面搜索  一般都是有边的
            R_found_point++;
        }
        if (R_found_point >8)                      //找到基准斜率边  做延长线重新确定无边   当有边的点数大于8
        {
          D_R = ((float)(ImageDeal[Ysite + R_found_point].RightBorder - ImageDeal[Ysite + 3].RightBorder)) /((float)(R_found_point - 3));
                                                  //求下面这些点连起来的斜率
                                                  //好给无边行做延长线左个基准
          if (D_R > 0) {
            R_Found_T ='T';                       //如果斜率大于0  那么找到了这个基准行  因为梯形畸变
                                                  //所以一般情况都是斜率大于0  小于0的情况也不用延长 没必要
          } else {
            R_Found_T = 'F';                      //没有找到这个基准行
            if (D_R < 0)
              ExtenRFlag = 'F';                   //这个标志位用于十字角点补线  防止图像误补用的
          }
        }
      }
      if (R_Found_T == 'T')
        ImageDeal[Ysite].RightBorder =ImageDeal[ytemp_W_R].RightBorder -D_R * (ytemp_W_R - Ysite);  //如果找到了 那么以基准行做延长线

      LimitL(ImageDeal[Ysite].RightBorder);  //限幅
      LimitH(ImageDeal[Ysite].RightBorder);  //限幅
    }

    if (ImageDeal[Ysite].IsLeftFind == 'W' && Ysite > 10 && Ysite < 50 &&
        ImageStatus.Road_type != Barn_in)    //下面同理  左边界
    {
      if (Get_L_line == 'F') {
        Get_L_line = 'T';
        ytemp_W_L = Ysite + 2;
        for (ysite = Ysite + 1; ysite < Ysite + 15; ysite++) {
          if (ImageDeal[ysite].IsLeftFind == 'T')
            L_found_point++;
        }
        if (L_found_point > 8)              //找到基准斜率边  做延长线重新确定无边
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

      LimitL(ImageDeal[Ysite].LeftBorder);  //限幅
      LimitH(ImageDeal[Ysite].LeftBorder);  //限幅
    }
}
    if (ImageDeal[Ysite].IsLeftFind == 'W'&&ImageDeal[Ysite].IsRightFind == 'W')
         {
             ImageStatus.WhiteLine++;  //要是左右都无边，丢边数+1
         }
        if (ImageDeal[Ysite].IsLeftFind == 'W'&&Ysite<55)
        {
             ImageStatus.Left_Line++;
        }
        if (ImageDeal[Ysite].IsRightFind == 'W'&&Ysite<55)
        {
             ImageStatus.Right_Line++;
        }


      LimitL(ImageDeal[Ysite].LeftBorder);   //限幅
      LimitH(ImageDeal[Ysite].LeftBorder);   //限幅
      LimitL(ImageDeal[Ysite].RightBorder);  //限幅
      LimitH(ImageDeal[Ysite].RightBorder);  //限幅

      ImageDeal[Ysite].Wide =ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;
      ImageDeal[Ysite].Center =(ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2;

    if (ImageDeal[Ysite].Wide <= 7)         //重新确定可视距离
    {
      ImageStatus.OFFLine = Ysite + 1;
      break;
    }

    else if (  ImageDeal[Ysite].RightBorder <= 10
             ||ImageDeal[Ysite].LeftBorder >= 70) {
              ImageStatus.OFFLine = Ysite + 1;
              break;
    }                                        //当图像宽度小于0或者左右边达到一定的限制时，则终止巡边
  }


  return;
}

//延长线绘制，理论上来说是很准确的
static void DrawExtensionLine(void)        //绘制延长线并重新确定中线 ，把补线补成斜线
{
  if ((
        ImageStatus.Road_type != Barn_in
        &&ImageStatus.Road_type != Ramp)
//        &&ImageStatus.pansancha_Lenth* OX==0
        &&ImageStatus.Road_type !=LeftCirque
        &&ImageStatus.Road_type !=RightCirque
        )                                  // g5.22  6.22调试注释  记得改回来
  {
    if (ImageStatus.WhiteLine >= ImageStatus.TowPoint_True - 15)
      TFSite = 55;
//    if (ImageStatus.CirqueOff == 'T' && ImageStatus.Road_type == LeftCirque)
//      TFSite = 55;
    if (ExtenLFlag != 'F')
      for (Ysite = 54; Ysite >= (ImageStatus.OFFLine + 4);
           Ysite--)                       //从第五行开始网上扫扫到顶边下面两行   多段补线
                                          //不仅仅只有一段
      {
        PicTemp = Pixle[Ysite];           //存当前行
        if (ImageDeal[Ysite].IsLeftFind =='W')                          //如果本行左边界没扫到但扫到的是白色，说明本行没有左边界点
        {
          //**************************************************//**************************************************
          if (ImageDeal[Ysite + 1].LeftBorder >= 70)                    //如果左边界实在是太右边
          {
            ImageStatus.OFFLine = Ysite + 1;
            break;                        //直接跳出（极端情况）
          }
          //************************************************//*************************************************

          while (Ysite >= (ImageStatus.OFFLine + 4))                    //此时还没扫到顶边
          {
            Ysite--;                      //继续往上扫
            if (  ImageDeal[Ysite].IsLeftFind == 'T'
                &&ImageDeal[Ysite - 1].IsLeftFind == 'T'
                &&ImageDeal[Ysite - 2].IsLeftFind == 'T'
                &&ImageDeal[Ysite - 2].LeftBorder > 0
                &&ImageDeal[Ysite - 2].LeftBorder <70
                )                                                       //如果扫到本行出现了并且本行以上连续三行都有左边界点（左边界在空白上方）
            {
              FTSite = Ysite - 2;          //把本行上面的第二行存入FTsite
              break;
            }
          }

          DetL =
              ((float)(ImageDeal[FTSite].LeftBorder -
                       ImageDeal[TFSite].LeftBorder)) /
              ((float)(FTSite - TFSite));  //左边界的斜率：列的坐标差/行的坐标差
          if (FTSite > ImageStatus.OFFLine)
            for (
                ytemp = TFSite; ytemp >= FTSite; ytemp--)               //从第一次扫到的左边界的下面第二行的坐标开始往上扫直到空白上方的左边界的行坐标值
            {
              ImageDeal[ytemp].LeftBorder =
                  (int)(DetL * ((float)(ytemp - TFSite))) +
                  ImageDeal[TFSite]
                      .LeftBorder;                                      //将这期间的空白处补线（补斜线），目的是方便图像处理
            }
        } else
          TFSite = Ysite + 2;                                           //如果扫到了本行的左边界，该行存在这里面，（算斜率）
      }

    if (ImageStatus.WhiteLine >= ImageStatus.TowPoint_True - 15)
      TFSite = 55;
    // g5.22
    if (ImageStatus.CirqueOff == 'T' && ImageStatus.Road_type == RightCirque)
      TFSite = 55;
    if (ExtenRFlag != 'F')
      for (Ysite = 54; Ysite >= (ImageStatus.OFFLine + 4);
           Ysite--)               //从第五行开始网上扫扫到顶边下面两行
      {
        PicTemp = Pixle[Ysite];  //存当前行

        if (ImageDeal[Ysite].IsRightFind =='W')                       //如果本行右边界没扫到但扫到的是白色，说明本行没有右边界点，但是处于赛道内的
        {
          if (ImageDeal[Ysite + 1].RightBorder <= 10)                 //如果右边界实在是太左边
          {
            ImageStatus.OFFLine =Ysite + 1;                           //直接跳出，说明这种情况赛道就尼玛离谱
            break;
          }
          while (Ysite >= (ImageStatus.OFFLine + 4))                  //此时还没扫到顶边下面两行
          {
            Ysite--;
            if (  ImageDeal[Ysite].IsRightFind == 'T'
                &&ImageDeal[Ysite - 1].IsRightFind == 'T'
                &&ImageDeal[Ysite - 2].IsRightFind == 'T'
                &&ImageDeal[Ysite - 2].RightBorder < 70
                &&ImageDeal[Ysite - 2].RightBorder > 10
                )                                                      //如果扫到本行出现了并且本行以上连续三行都有左边界点（左边界在空白上方）
            {
              FTSite = Ysite - 2;                                      // 把本行上面的第二行存入FTsite
              break;
            }
          }

          DetR =((float)(ImageDeal[FTSite].RightBorder -ImageDeal[TFSite].RightBorder)) /((float)(FTSite - TFSite));         //右边界的斜率：列的坐标差/行的坐标差
          if (FTSite > ImageStatus.OFFLine)
            for (ytemp = TFSite; ytemp >= FTSite;ytemp--)              //从第一次扫到的右边界的下面第二行的坐标开始往上扫直到空白上方的右边界的行坐标值
            {
              ImageDeal[ytemp].RightBorder =(int)(DetR * ((float)(ytemp - TFSite))) +ImageDeal[TFSite].RightBorder;          //将这期间的空白处补线（补斜线），目的是方便图像处理
            }
        } else
          TFSite =Ysite +2;                                           //如果本行的右边界找到了，则把该行下面第二行坐标送个TFsite
      }
  }
  for (Ysite = 59; Ysite >= ImageStatus.OFFLine; Ysite--) {
    ImageDeal[Ysite].Center =(ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) /2;                                //扫描结束，把这一块经优化之后的中间值存入
    ImageDeal[Ysite].Wide =-ImageDeal[Ysite].LeftBorder +ImageDeal[Ysite].RightBorder;                                       //把优化之后的宽度存入
  }
}
/*上交大左右手法则扫线，作为处理圆环等判断元素的第二依据*/
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name           Search_Bottom_Line_OTSU
//  @brief          获取底层左右边线
//  @param          imageInput[IMAGE_ROW][IMAGE_COL]        传入的图像数组
//  @param          Row                                     图像的Ysite
//  @param          Col                                     图像的Xsite
//  @return         Bottonline                              底边行选择
//  @time           2022年10月9日
//  @Author
//  Sample usage:   Search_Bottom_Line_OTSU(imageInput, Row, Col, Bottonline);
//--------------------------------------------------------------------------------------------------------------------------------------------

void Search_Bottom_Line_OTSU(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline)
{

    //寻找左边边界
    for (int Xsite = Col / 2-2; Xsite > 1; Xsite--)
    {
        if (imageInput[Bottonline][Xsite] == 1 && imageInput[Bottonline][Xsite - 1] == 0)
        {
            ImageDeal[Bottonline].LeftBoundary = Xsite;//获取底边左边线
            break;
        }
    }
    for (int Xsite = Col / 2+2; Xsite < LCDW-1; Xsite++)
    {
        if (imageInput[Bottonline][Xsite] == 1 && imageInput[Bottonline][Xsite + 1] == 0)
        {
            ImageDeal[Bottonline].RightBoundary = Xsite;//获取底边右边线
            break;
        }
    }

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name           Search_Left_and_Right_Lines
//  @brief          通过sobel提取左右边线
//  @param          imageInput[IMAGE_ROW][IMAGE_COL]        传入的图像数组
//  @param          Row                                     图像的Ysite
//  @param          Col                                     图像的Xsite
//  @param          Bottonline                              底边行选择
//  @return         无
//  @time           2022年10月7日
//  @Author
//  Sample usage:   Search_Left_and_Right_Lines(imageInput, Row, Col, Bottonline);
//--------------------------------------------------------------------------------------------------------------------------------------------

void Search_Left_and_Right_Lines(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline)
{
//定义小人的当前行走状态位置为 上 左 下 右 一次要求 上：左边为黑色 左：上边为褐色 下：右边为色  右：下面有黑色
/*  前进方向定义：
                *   0
                * 3   1
                *   2
*/
/*寻左线坐标规则*/
    uint8 Left_Rule[2][8] = {
                                  {0,-1,1,0,0,1,-1,0 },//{0,-1},{1,0},{0,1},{-1,0},  (x,y )
                                  {-1,-1,1,-1,1,1,-1,1} //{-1,-1},{1,-1},{1,1},{-1,1}
    };
    /*寻右线坐标规则*/
    int Right_Rule[2][8] = {
                              {0,-1,1,0,0,1,-1,0 },//{0,-1},{1,0},{0,1},{-1,0},
                              {1,-1,1,1,-1,1,-1,-1} //{1,-1},{1,1},{-1,1},{-1,-1}
    };
      int num=0;
    uint8 Left_Ysite = Bottonline;
    uint8 Left_Xsite = ImageDeal[Bottonline].LeftBoundary;
    uint8 Left_Rirection = 0;//左边方向
    uint8 Pixel_Left_Ysite = Bottonline;
    uint8 Pixel_Left_Xsite = 0;

    uint8 Right_Ysite = Bottonline;
    uint8 Right_Xsite = ImageDeal[Bottonline].RightBoundary;
    uint8 Right_Rirection = 0;//右边方向
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
        /*********左边巡线*******/
        if ((Pixel_Left_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary)//右边扫线
        {
            /*计算前方坐标*/
            Pixel_Left_Ysite = Left_Ysite + Left_Rule[0][2 * Left_Rirection + 1];
            Pixel_Left_Xsite = Left_Xsite + Left_Rule[0][2 * Left_Rirection];

            if (imageInput[Pixel_Left_Ysite][Pixel_Left_Xsite] == 0)//前方是黑色
            {
                //顺时针旋转90
                if (Left_Rirection == 3)
                    Left_Rirection = 0;
                else
                    Left_Rirection++;
            }
            else//前方是白色
            {
                /*计算左前方坐标*/
                Pixel_Left_Ysite = Left_Ysite + Left_Rule[1][2 * Left_Rirection + 1];
                Pixel_Left_Xsite = Left_Xsite + Left_Rule[1][2 * Left_Rirection];

                if (imageInput[Pixel_Left_Ysite][Pixel_Left_Xsite] == 0)//左前方为黑色
                {
                    //方向不变  Left_Rirection
                    Left_Ysite = Left_Ysite + Left_Rule[0][2 * Left_Rirection + 1];
                    Left_Xsite = Left_Xsite + Left_Rule[0][2 * Left_Rirection];
                    if (ImageDeal[Left_Ysite].LeftBoundary_First == 0){
                        ImageDeal[Left_Ysite].LeftBoundary_First = Left_Xsite;
                        ImageDeal[Left_Ysite].LeftBoundary = Left_Xsite;
                    }
                }
                else//左前方为白色
                {
                    // 方向发生改变 Left_Rirection  逆时针90度
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
        /*********右边巡线*******/
        if ((Pixel_Right_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary)//右边扫线
        {
            /*计算前方坐标*/
            Pixel_Right_Ysite = Right_Ysite + Right_Rule[0][2 * Right_Rirection + 1];
            Pixel_Right_Xsite = Right_Xsite + Right_Rule[0][2 * Right_Rirection];

            if (imageInput[Pixel_Right_Ysite][Pixel_Right_Xsite] == 0)//前方是黑色
            {
                //逆时针旋转90
                if (Right_Rirection == 0)
                    Right_Rirection = 3;
                else
                    Right_Rirection--;
            }
            else//前方是白色
            {
                /*计算右前方坐标*/
                Pixel_Right_Ysite = Right_Ysite + Right_Rule[1][2 * Right_Rirection + 1];
                Pixel_Right_Xsite = Right_Xsite + Right_Rule[1][2 * Right_Rirection];

                if (imageInput[Pixel_Right_Ysite][Pixel_Right_Xsite] == 0)//左前方为黑色
                {
                    //方向不变  Right_Rirection
                    Right_Ysite = Right_Ysite + Right_Rule[0][2 * Right_Rirection + 1];
                    Right_Xsite = Right_Xsite + Right_Rule[0][2 * Right_Rirection];
                    if (ImageDeal[Right_Ysite].RightBoundary_First == 79 )
                        ImageDeal[Right_Ysite].RightBoundary_First = Right_Xsite;
                    ImageDeal[Right_Ysite].RightBoundary = Right_Xsite;
                }
                else//左前方为白色
                {
                    // 方向发生改变 Right_Rirection  逆时针90度
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

        if (abs(Pixel_Right_Xsite - Pixel_Left_Xsite) < 3)//Ysite<80是为了放在底部是斑马线扫描结束  3 && Ysite < 30
        {

            ImageStatus.OFFLineBoundary = Ysite;
            break;
        }

    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name           Search_Border_OTSU
//  @brief          通过OTSU获取边线 和信息
//  @param          imageInput[IMAGE_ROW][IMAGE_COL]        传入的图像数组
//  @param          Row                                     图像的Ysite
//  @param          Col                                     图像的Xsite
//  @param          Bottonline                              底边行选择
//  @return         无
//  @time           2022年10月7日
//  @Author
//  Sample usage:   Search_Border_OTSU(mt9v03x_image, IMAGE_ROW, IMAGE_COL, IMAGE_ROW-8);
//--------------------------------------------------------------------------------------------------------------------------------------------

void Search_Border_OTSU(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline)
{
    ImageStatus.WhiteLine_L = 0;
    ImageStatus.WhiteLine_R = 0;
    //ImageStatus.OFFLine = 1;
    /*封上下边界处理*/
    for (int Xsite = 0; Xsite < LCDW; Xsite++)
    {
        imageInput[0][Xsite] = 0;
        imageInput[Bottonline + 1][Xsite] = 0;
    }
    /*封左右边界处理*/
    for (int Ysite = 0; Ysite < LCDH; Ysite++)
    {
            ImageDeal[Ysite].LeftBoundary_First = 0;
            ImageDeal[Ysite].RightBoundary_First = 79;

            imageInput[Ysite][0] = 0;
            imageInput[Ysite][LCDW - 1] = 0;
    }
    /********获取底部边线*********/
    Search_Bottom_Line_OTSU(imageInput, Row, Col, Bottonline);
    /********获取左右边线*********/
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

//出现丢边的时候  重新确定无边行的中线
static void RouteFilter(void) {
//  if(ImageStatus.Road_type != RightCirque && ImageStatus.Road_type != LeftCirque)
//  {
  for (Ysite = 58; Ysite >= (ImageStatus.OFFLine + 5);   //原本58
       Ysite--)                                     //从开始位到停止位
  {
    if (   ImageDeal[Ysite].IsLeftFind == 'W'
         &&ImageDeal[Ysite].IsRightFind == 'W'
         &&Ysite <= 45
         &&ImageDeal[Ysite - 1].IsLeftFind == 'W'
         &&ImageDeal[Ysite - 1].IsRightFind =='W')  //当前行左右都无边，而且在前45行   滤波
    {
      ytemp = Ysite;
      while (ytemp >= (ImageStatus.OFFLine +5))     // 改改试试，-6效果好一些   原本+5
      {
        ytemp--;
        if (  ImageDeal[ytemp].IsLeftFind == 'T'
            &&ImageDeal[ytemp].IsRightFind == 'T')  //寻找两边都正常的，找到离本行最近的就不找了
        {
          DetR = (float)(ImageDeal[ytemp - 1].Center - ImageDeal[Ysite + 2].Center) /(float)(ytemp - 1 - Ysite - 2);          //算斜率
          int CenterTemp = ImageDeal[Ysite + 2].Center;
          int LineTemp = Ysite + 2;
          while (Ysite >= ytemp) {
            ImageDeal[Ysite].Center =(int)(CenterTemp +DetR * (float)(Ysite - LineTemp));                                     //用斜率补
            Ysite--;
          }
          break;
        }
      }
    }
    ImageDeal[Ysite].Center =(ImageDeal[Ysite - 1].Center + 2 * ImageDeal[Ysite].Center) /3;                                  //求平均，应该会比较滑  本来是上下两点平均
  }
//  }
}

int icm_start_test_cross = 0;  //开启icm积分标志位

/****十字检测*****/  //上面的算法已经滤除了十字  相当于不要处理
void Cross_Test() {
  if (ImageStatus.OFFLine > 15)                       //当可视距离比较近的时候 开启积分处理  用于特殊处理270°弯道之后的十字
    icm_start_test_cross = 1;
  else
    icm_start_test_cross = 0;

  if (abs(tuoluoyijifen) > 100)
    ImageStatus.Road_type = Cross;
//  if (ImageStatus.Road_type == Cross && ImageStatus.Cross_Lenth * OX > 100)
//    ImageStatus.Road_type = 0;
}

//获取单行黑点数量  最后没有用到
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


 //找最近边   最后没有用到
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

    //找反向近边
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

/****圆环检测***/
uint8 Pass_flag = 'F';
//uint8 Left_Less_Num = 0;
//环岛检测
int ceshi_flag;
//--------------------------------------------------------------
//  @name           Element_Judgment_Left_Rings()
//  @brief          整个图像判断的子函数，用来判断左圆环类型.
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
//  @brief          整个图像判断的子函数，用来判断右圆环类型.
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
        ImageFlag.ring_big_small=1;     //小环
        ImageStatus.Road_type = RightCirque;
    }
    Ring_Help_Flag = 0;
}
//左圆环处理
void Element_Handle_Left_Rings(void)
{
    /***************************************进程**************************************/
    int num = 0;
    for (int Ysite = 55; Ysite > 30; Ysite--)
    {
        if(ImageDeal[Ysite].IsLeftFind == 'W')
            num++;
        if(    ImageDeal[Ysite+3].IsLeftFind == 'W' && ImageDeal[Ysite+2].IsLeftFind == 'W'
            && ImageDeal[Ysite+1].IsLeftFind == 'W' && ImageDeal[Ysite].IsLeftFind == 'T')
            break;
    }
        //准备进环
    if (ImageFlag.image_element_rings_flag == 1 && num>10)
    {
        ImageFlag.image_element_rings_flag = 2;
    }
    if (ImageFlag.image_element_rings_flag == 2 && num<8)
    {
        ImageFlag.image_element_rings_flag = 5;
    }
        //进环
    if(ImageFlag.image_element_rings_flag == 5 && /*num>15)*/ImageStatus.Right_Line>25)
    {
        ImageFlag.image_element_rings_flag = 6;
    }
        //进环小圆环
    if(ImageFlag.image_element_rings_flag == 6 && ImageStatus.Right_Line<3)
    {
        ImageFlag.image_element_rings_flag = 7;
    }
        //环内 大圆环判断
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
    //出环后
    if (ImageFlag.image_element_rings_flag == 8)
    {
        if (
                //Straight_Judge(2, ImageStatus.OFFLine+15, 50) < 1
                ImageStatus.Right_Line < 8     // 经过在华理轻工测试发现圆环出环跳变补直线过早，加强条件
                && ImageStatus.OFFLine < 13
                )    //右边为直线且截止行（前瞻值）很小
        {
            ImageFlag.image_element_rings_flag = 9;
        }
    }
    //结束圆环进程
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
            ImageStatus.Road_type = 0;   //出环处理完道路类型清0
            ImageFlag.image_element_rings_flag = 0;
            ImageFlag.image_element_rings = 0;
            ImageFlag.ring_big_small = 0;
        }
    }
    /***************************************处理**************************************/
        //准备进环  半宽处理
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
        //进环  补线
    if  ( ImageFlag.image_element_rings_flag == 5
        ||ImageFlag.image_element_rings_flag == 6
        )
    {
        int  flag_Xsite_1=0;
        int flag_Ysite_1=0;
        float Slope_Rings=0;
        for(Ysite=55;Ysite>ImageStatus.OFFLine;Ysite--)//下面弧点
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
        if(flag_Ysite_1 == 0)   //意外：找不到弧点。
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
        //补线
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
            for(Ysite=flag_Ysite_1-1;Ysite>10;Ysite--) //A点上方进行扫线
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
    //环内不处理
    if (ImageFlag.image_element_rings_flag == 7){}
        //大圆环出环 补线
    if (ImageFlag.image_element_rings_flag == 8 && ImageFlag.ring_big_small == 1)    //大圆环
    {
        Repair_Point_Xsite = 20;
        Repair_Point_Ysite = 5;
        for (int Ysite = 40; Ysite > 5; Ysite--)
        {
            if (Pixle[Ysite][23] == 1 && Pixle[Ysite-1][23] == 0)//20
            {
                Repair_Point_Xsite =23;
                Repair_Point_Ysite= Ysite-1;
                ImageStatus.OFFLine = Ysite + 1;  //截止行重新规划
                break;
            }
        }
        for (int Ysite = 57; Ysite > Repair_Point_Ysite-3; Ysite--)//补线
        {
            ImageDeal[Ysite].RightBorder = (ImageDeal[58].RightBorder - Repair_Point_Xsite) * (Ysite - 58) / (58 - Repair_Point_Ysite)  + ImageDeal[58].RightBorder;
           // ImageDeal[Ysite].RightBorder = ImageDeal[Ysite].LeftBorder + Half_Bend_Wide[Ysite];
            if(ImageDeal[Ysite].RightBorder>77){ImageDeal[Ysite].RightBorder = 77;}
            ImageDeal[Ysite].Center = ((ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2);
        }
    }
        //已出环 半宽处理
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
//  @brief          整个图像处理的子函数，用来处理右圆环类型.
//  @parameter      void
//  @time
//  @Author         MRCHEN
//  Sample usage:   Element_Handle_Right_Rings();
//-------------------------------------------------------------
void Element_Handle_Right_Rings()
{
    /****************进程*****************/
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
        //准备进环
    if (ImageFlag.image_element_rings_flag == 1 && num>10)
    {
        ImageFlag.image_element_rings_flag = 2;
    }
    if (ImageFlag.image_element_rings_flag == 2 && num<5)
    {
        ImageFlag.image_element_rings_flag = 5;
    }
        //进环
    if(ImageFlag.image_element_rings_flag == 5 && ImageStatus.Left_Line>8)
    {
        ImageFlag.image_element_rings_flag = 6;
    }
        //进环小圆环
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
             /*&&*/ ImageStatus.Left_Line < 10 //经过在华理轻工的赛道测试，发现圆环出环跳变状态过早，加强跳变条件的约束
             && ImageStatus.OFFLine < 16)    //右边为直线且截止行（前瞻值）很小
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
            ImageStatus.Road_type = 0;   //出环处理完道路类型清0
            ImageFlag.image_element_rings_flag = 0;
            ImageFlag.image_element_rings = 0;
            ImageFlag.ring_big_small = 0;
        }
    }
    /***************************************处理**************************************/
         //准备进环  半宽处理
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
        //进环  补线
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
        //补线
        if(flag_Ysite_1!=0)
        {
            for(Ysite=flag_Ysite_1;Ysite<58;Ysite++)
            {
                ImageDeal[Ysite].LeftBorder=flag_Xsite_1+Slope_Right_Rings*(Ysite-flag_Ysite_1);
                ImageDeal[Ysite].Center=(ImageDeal[Ysite].LeftBorder+ImageDeal[Ysite].RightBorder)/2;//板块
                if(ImageDeal[Ysite].Center>79)
                    ImageDeal[Ysite].Center=79;
            }
            ImageDeal[flag_Ysite_1].LeftBorder=flag_Xsite_1;
            for(Ysite=flag_Ysite_1-1;Ysite>10;Ysite--) //A点上方进行扫线
            {
                for(Xsite=ImageDeal[Ysite+1].LeftBorder+8;Xsite>ImageDeal[Ysite+1].LeftBorder-4;Xsite--)
                {
                    if(Pixle[Ysite][Xsite]==1 && Pixle[Ysite][Xsite-1]==0)
                    {
                     ImageDeal[Ysite].LeftBorder=Xsite;
                     ImageDeal[Ysite].Wide=ImageDeal[Ysite].RightBorder-ImageDeal[Ysite].LeftBorder;
                     ImageDeal[Ysite].Center=(ImageDeal[Ysite].LeftBorder+ImageDeal[Ysite].RightBorder)/2;//板块
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
        //环内不处理
    if (ImageFlag.image_element_rings_flag == 7){}
        //大圆环出环 补线
    if (ImageFlag.image_element_rings_flag == 8)  //大圆环
    {
        Repair_Point_Xsite = 39;
        Repair_Point_Ysite = 7;
        for (int Ysite = 40; Ysite > 5; Ysite--)
        {
            if (Pixle[Ysite][39] == 1 && Pixle[Ysite-1][39] == 0)
            {
                Repair_Point_Xsite = 39;
                Repair_Point_Ysite = Ysite-1;
                ImageStatus.OFFLine = Ysite + 1;  //截止行重新规划
                break;
            }
        }
        for (int Ysite = 57; Ysite > Repair_Point_Ysite-3; Ysite--)         //补线
        {
            ImageDeal[Ysite].LeftBorder = (ImageDeal[58].LeftBorder - Repair_Point_Xsite) * (Ysite - 58) / (58 - Repair_Point_Ysite)  + ImageDeal[58].LeftBorder;
            //ImageDeal[Ysite].LeftBorder = ImageDeal[Ysite].RightBorder -  Half_Bend_Wide[Ysite]-11;
            if(ImageDeal[Ysite].LeftBorder<3){ImageDeal[Ysite].LeftBorder = 3;}
            ImageDeal[Ysite].Center = (ImageDeal[Ysite].RightBorder + ImageDeal[Ysite].LeftBorder) / 2;
        }
    }
    //已出环 半宽处理
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
//uint8 Circle_Off = 'F';  //关闭圆环的状态位  由有无边决定
//uint8 Out_Flag = 0;      //是否找到出环角点
//int circleoff_lenth;     //出环防误判距离
//int circle_just_one=1;
//
//
////环岛检测
//void CircleTest() {
// // if(adcsum>4200)
//  if ( (adcsum >= 5000)/*||(adcleft>2000&&adcright<800)||(adcleft<800&&adcright>2000) */   //3800
//      &&ImageStatus.CirqueOut != 'T'
//      && ImageStatus.CirquePass != 'T'
//      &&ImageStatus.CirqueOff !='T')                              //电磁大于某个阈值并且没有处于圆环中  那么检测到圆环
//  {
//    ImageStatus.IsCinqueOutIn = 'T';                              //此标志位用于圆环补线
//  }
//
//  if (ImageStatus.IsCinqueOutIn == 'T')                           //判断是左还是右
//  {
//    for (Ysite = 55; Ysite > (ImageStatus.OFFLine + 2); Ysite--)  //左圆环
//    {
//      if ((ImageDeal[Ysite].LeftBorder + 8 < ImageDeal[Ysite - 2].LeftBorder)
//         &&ImageStatus.Road_type != RightCirque) {
//        ImageStatus.Road_type = LeftCirque;
//        Pass_flag = 'F';
//        break;
//      }
//      else if (( ImageDeal[Ysite].RightBorder - 8 >ImageDeal[Ysite - 2].RightBorder)
//               &&ImageStatus.Road_type != LeftCirque)               //右圆环
//      {
//        ImageStatus.Road_type = RightCirque;
//        Pass_flag = 'F';
//        break;
//      }
//      Pass_flag ='T';
//                                                                    // 已经识别到圆环圆环但是没有找到左右特征点说明这时候已经进入圆环了
//                                                                    // 跳出就可以改标志位了
//    }
//
//    if (Pass_flag == 'T')                                           //没有识别到左右特征点说明已经进环岛
//    {
//      if (ImageStatus.Cirque1lenth*OX > 140)                     // 环岛里面电磁信号低 说明已经进入圆环
//                                                                    // 有点问题感觉入环到环中需要改进方案
//      {
//        ImageStatus.CirquePass ='T';                                //此标志表示已经进入到圆环中  通过这个标志位取消入环补线
//        ImageStatus.IsCinqueOutIn = 'F';
//        Pass_flag = 'F';                                            //清除标志位
//      }
//    }
//  }
//
//  if (ImageStatus.CirquePass == 'T' &&ImageStatus.Pass_Lenth * OX > 50)    //已经进入环之后就要判断出环点 //g5.22
//                                                                            //还没写 仪 这个有点不稳
//  {
//    if (ImageStatus.Road_type == RightCirque)                               //右圆环的情况
//    {
//      for (Ysite = 53; Ysite > (ImageStatus.OFFLine + SystemData.OutCicle_line);Ysite--)  //右圆环出环看到的是左边的角  识别这个角就行
//                                                                                          //但是截至行数不能太前  上半部分的图像不是很稳
//      {
//        if (((  ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite -10].LeftBorder >1)         //中间大上下小的特征
//             &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite +10].LeftBorder > 1))
//             ||(ImageDeal[Ysite + 1].IsLeftFind == 'T'
//              &&ImageDeal[Ysite].IsLeftFind == 'T'
//              &&ImageDeal[Ysite - 1].IsLeftFind == 'W')) {
//          ImageStatus.CirquePass = 'F';
//          ImageStatus.IsCinqueOutIn = 'F';
//          ImageStatus.CirqueOut = 'T';                                                    //识别到角点  此时状态变成出环状态
//
//          break;
//        }
//      }
//    }
//
//    if (ImageStatus.Road_type == LeftCirque)                                              //g和上面同理  左圆环
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
//  if (ImageStatus.CirqueOut == 'T')                       //在出环的状态  会有出环的补线处理  但也要判断什么时候停止补线
//                                                          //没加陀螺仪  下面的逻辑不是很稳  因为图像有时候有点搞
//  {
//   if (ImageStatus.Cirque2lenth*OX>272 )          //   如果出环后停止补线的特征都齐了
//                                                          // 那么就结束圆环  基本回到开机状态
// //      if((adcsum >= 2000)||(adcleft>2200&&adcright<700)||(adcleft<700&&adcright>2200))
//    {
//      ImageStatus.CirquePass = 'F';
//      ImageStatus.IsCinqueOutIn = 'F';
//      ImageStatus.CirqueOut = 'F';
//      ImageStatus.CirqueOff = 'T';                        //此标志表示出环后需要过一段距离再判断入环  防止二次入环
//    }
//  }
//
//  if (ImageStatus.CirqueOff == 'T'
//      &&ImageStatus.Out_Lenth * OX >140)                 //在结束出环后的1-2m将所有标志位初始化，（防止二次进环//150
//                                                          //距离消抖）将OFF标志清楚 回到最开机状态
//  {   ImageStatus.sanchaju = 1;
//      ImageStatus.CirquePass = 'F';
//      ImageStatus.IsCinqueOutIn = 'F';
//      ImageStatus.CirqueOut = 'F';
//      ImageStatus.CirqueOff = 'F';
//      ImageStatus.Road_type = 0;  //回到原来的状态
//      circle_just_one=0;
//      SystemData.clrcle_num++;
//  }
//}
//
//static int Yjump1 = 0;
//int circle_r = 10;
//float circlk_k = 1.02;
//void Circle_Handle() {
//    //入环补线
//  if (ImageStatus.IsCinqueOutIn == 'T')                           //此时处于入环状态
//  {
//    //左圆环
//    if (ImageStatus.Road_type == LeftCirque) {
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine + 2; Ysite--)  //找到补线点
//      {
//        if (ImageDeal[Ysite].LeftBorder + 8 < ImageDeal[Ysite - 2].LeftBorder) {
//          Yjump1 = Ysite;
//          ImageStatus.OFFLine = Yjump1;
//          break;
//        }
//      }
//
//      if (Yjump1 > 0) {                                           //开始补线
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
//    //右圆环
//    if (ImageStatus.Road_type == RightCirque) {
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine + 2; Ysite--)  //找到补线点
//      {
//        if (ImageDeal[Ysite].RightBorder - 8 >ImageDeal[Ysite - 2].RightBorder) {
//            Yjump1 = Ysite;
//            ImageStatus.OFFLine = Yjump1;
//            break;
//        }
//      }
//
//      if (Yjump1 > 0) {                                           //开始补线
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
//  ////出环补线
//
//  if (ImageStatus.CirqueOut == 'T')  //此时处于出环状态
//  {
//    //左圆环
//    float Det_R;
//    if (ImageStatus.Road_type == LeftCirque) {
//      Det_R = circlk_k * 79 / (55 - ImageStatus.OFFLine);                         //计算补线斜率
//      for (Ysite = 55; Ysite > ImageStatus.OFFLine; Ysite--) {
//        int temp = (int)(ImageDeal[55].RightBorder - Det_R * (55 - Ysite));
//        if (temp < 0) {
//          temp = 0;
//        }
//        if (temp < ImageDeal[Ysite].RightBorder) {                                //补线
//          ImageDeal[Ysite].RightBorder = temp;
//          ImageDeal[Ysite].LeftBorder = 0;
//          ImageDeal[Ysite].Center =(ImageDeal[Ysite].LeftBorder + ImageDeal[Ysite].RightBorder) / 2;
//          ImageDeal[Ysite].Wide =ImageDeal[Ysite].RightBorder - ImageDeal[Ysite].LeftBorder;
//        }
//      }
//    }
////同上
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
//三岔口检测
uint8 f1 = 0;  //没用
uint8 f2 = 0;  //没用
uint8 f3 = 0;  //没用
uint8 Fork_in_1 = 0;//近端特征点
uint8 Fork_in_2 = 0;//远端特征点
uint8 Fork_in = 0;  //入三叉标志
uint8 ForkLinePointx_l = 0;//三叉倒三角左边列
uint8 ForkLinePointx_r = 0;//三叉倒三角右边列
int ForkLinePointy = 0;    //三叉倒三角底边行
int Fork1_Y = 0;           //三叉近端特征行
int Fork2_Y = 0;           //三叉远端特征行
int Fork_dowm = 0;         //三叉减速标志  编码器积分退出
//void ForkTest() {
//  int wide = 0;   //临时变量
////  int Fork_thr;   //切换强弱判断的阈值
////  if (SystemData.Model < 2)
////    Fork_thr = 5000;
////  else
////    Fork_thr = 5000;
////     Fork_thr=5000;
//  //找由直道变到岔道的第一特征
// if (adcsum > 800)                 //在三叉口以外的
//  {
//    for (Ysite = 53; Ysite > (ImageStatus.OFFLine + 6);Ysite--)   //防止Ysite溢出
//
//    {
//      if ((  ImageDeal[Ysite].IsRightFind == 'T'
//           &&ImageDeal[Ysite + 1].IsRightFind == 'T')
//          ||(ImageDeal[Ysite].IsLeftFind == 'T'
//           &&ImageDeal[Ysite + 1].IsLeftFind =='T'))            //进三叉的时候一般会看见左右两边120*的圆角
//      {
//        if (((ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite - 6].LeftBorder) >2
//             &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite - 6].LeftBorder) <8
//            &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite + 6].LeftBorder) >2
//             &&(ImageDeal[Ysite].LeftBorder - ImageDeal[Ysite + 6].LeftBorder) <8)        //左边的角
//            ||((ImageDeal[Ysite - 6].RightBorder - ImageDeal[Ysite].RightBorder) >2
//             &&(ImageDeal[Ysite - 6].RightBorder - ImageDeal[Ysite].RightBorder) <8
//           // &&(ImageDeal[Ysite + 6].RightBorder - ImageDeal[Ysite].RightBorder) >2       //右边的角 看到一个就可以  因为看到两个经常漏判
//           //  &&(ImageDeal[Ysite + 6].RightBorder -ImageDeal[Ysite].RightBorder) < 8
//             ))     //阈值需要调整
//        {
//          Fork_in_1 = 'T';  //表示近端的角点特征找到
//          Fork1_Y = Ysite;  //记录第一特征点的行数
//          break;
//        }
//
//        else {
//          Fork_in_1 = 'F';  //没找到GG
//        }
//      }
//    }
//
//    //第二特征  找黑色三角块  并运算得到相关图像信息
//    for (Ysite = Fork1_Y; Ysite > (ImageStatus.OFFLine);Ysite--)                                          //从第一特征点开始往上搜索
//    {
//      PicTemp = Pixle[Ysite];
//      for (Xsite = ImageDeal[Ysite].LeftBorder; Xsite < 50;Xsite++)                                       //找三叉口黑色三角块
//      {
//        if ((*(PicTemp + Xsite) != 0) && (*(PicTemp + Xsite + 1) == 0) &&(*(PicTemp + Xsite + 2) == 0))   //找到黑色角快的左边
//        {
//          ImageDeal[Ysite].Black_Wide_L = Xsite + 1;                                                       //记录此时的左黑边界
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_L =ImageDeal[Ysite].Center;                                          //没找到就在中点
//      }
//
//      for (Xsite = ImageDeal[Ysite].RightBorder; Xsite > 30;Xsite--)                                       //找三叉口黑色三角块
//      {
//        if (  (*(PicTemp + Xsite) == 0)
//           && (*(PicTemp + Xsite - 1) == 0)
//            &&(*(PicTemp + Xsite + 1) != 0))      //找到黑色角快的右边
//        {
//          ImageDeal[Ysite].Black_Wide_R = Xsite;  //记录此时的右黑边界
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_R = ImageDeal[Ysite].Center;                                          //没找到就在中点
//      }
//
//      for (Xsite = ImageDeal[Ysite].Black_Wide_L;
//           Xsite <= ImageDeal[Ysite].Black_Wide_R; Xsite++) {
//        if (ImageDeal[Ysite].Black_Wide_L == ImageDeal[Ysite].Center
//            ||ImageDeal[Ysite].Black_Wide_R ==ImageDeal[Ysite].Center)                                       //如果是中点值那么GG因为这是没找到
//          break;
//        else if ((*(PicTemp + Xsite) == 0))     //数数左黑和右黑之间的黑点数
//        {
//          wide++;                               //计算找到三角块的本行黑点数
//        }
//      }
//
//      ImageDeal[Ysite].BlackWide = wide;        //记录这个宽度
//      ImageDeal[Ysite].Black_Pro =ImageDeal[Ysite].BlackWide / ImageDeal[Ysite].Wide;                         //图像黑点比例
//      wide = 0;                                 //清0
//    }
//
//    //判断是否为三叉的黑色三角块
//    for (Ysite = Fork1_Y; Ysite >= (ImageStatus.OFFLine + 1); Ysite--)  // g
//    {
//      if (( ImageDeal[Ysite].BlackWide - ImageDeal[Ysite + 3].BlackWide) >=2 //如果这个左黑和右黑之间黑点数比较多 并且满足三角形的形状
//          &&ImageDeal[Ysite].BlackWide > 21
//          &&ImageDeal[Ysite + 1].BlackWide > 17
//          &&ImageDeal[Ysite - 1].BlackWide > 17
//          &&(39 - ImageDeal[Ysite].Black_Wide_L) > 0                        //滤除斜十字
//          &&(ImageDeal[Ysite].Black_Wide_R - 39) > 0) {
//        ForkLinePointx_r = ImageDeal[Ysite].Black_Wide_R;                   //用于补线的点
//        ForkLinePointx_l = ImageDeal[Ysite].Black_Wide_L;
//        ForkLinePointy = Ysite;
//        Fork2_Y = Ysite;                                                    //记录第二特征点的行数
//        if (Fork1_Y - Fork2_Y > 6)
//        {
//          Fork_in_2 ='T';                                                   //当两特征点行数大于10   才判断为入环特征点  用于防误判
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
////  已经进入三叉口   降低分辨阈值  更好地识别出岔口   就不用识别第一特征点
////  只要识别第二特征点 同上
// else if (adcsum < 800)
//  {
//    //第二特征  找黑色三角块  并运算得到相关图像信息
//    for (Ysite = 55; Ysite > (ImageStatus.OFFLine); Ysite--)
//    {
//      PicTemp = Pixle[Ysite];
//      for (Xsite = ImageDeal[Ysite].LeftBorder; Xsite < 55;Xsite++)  //找三叉口黑色三角块
//      {
//        if ((  *(PicTemp + Xsite) != 0)
//            &&(*(PicTemp + Xsite + 1) == 0)
//            &&(*(PicTemp + Xsite + 2) == 0))                          //找到黑色角快左边
//        {
//          ImageDeal[Ysite].Black_Wide_L = Xsite + 1;
//          break;
//        } else
//          ImageDeal[Ysite].Black_Wide_L = ImageDeal[Ysite].Center;
//      }
//
//      for (Xsite = ImageDeal[Ysite].RightBorder; Xsite > 25;Xsite--)  //找三叉口黑色三角块//g
//      {
//        if ((   *(PicTemp + Xsite) == 0)
//             &&(*(PicTemp + Xsite - 1) == 0)
//             &&(*(PicTemp + Xsite + 1) != 0))                         //找到黑色角快右边
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
//      ImageDeal[Ysite].Black_Pro =ImageDeal[Ysite].BlackWide / ImageDeal[Ysite].Wide;  //图像黑点比例
//      wide = 0;
//      if (ImageDeal[Ysite].BlackWide > 2)
//        ImageDeal[Ysite].isBlackFind = 'T';
//      else
//        ImageDeal[Ysite].isBlackFind = 'F';
//    }
//
//    //判断是否为三叉的黑色三角块
//    for (Ysite = 55; Ysite >= (ImageStatus.OFFLine); Ysite--)  // g
//    {
//      if (( ImageDeal[Ysite].BlackWide - ImageDeal[Ysite + 3].BlackWide) > 1
//          &&ImageDeal[Ysite].BlackWide > 16
//          &&ImageDeal[Ysite + 1].BlackWide > 15
//          && (39 - ImageDeal[Ysite].Black_Wide_L) > 0                                 //滤除斜十字
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
//      &&(yuansanshu == 1))                                           //第一圈右补线
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
//      ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //宽度更新
//    }
//  }
//  if ((ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout) &&
//         ( yuansanshu == 0))   //第二圈左补线
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
//      ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //宽度更新
//    }
//  }
//}



//void Fork_Handle2() {
// // float Det_Fork_L;
//  //float Det_Fork_R;
//  int yuansanshu;
//  yuansanshu=SystemData.clrcle_num%2;
//  if (  (ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout)
//      &&(yuansanshu == 1))                                           //第一圈右补线
//  {
//      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--) {
//      ImageDeal[Ysite].Center = ImageDeal[Ysite].LeftBorder + buxianwide[Ysite]*0.5;}
//      //ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //宽度更新
//   //   Fit1(59,50);
//    }
//
//  if ((ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout) &&
//         ( yuansanshu == 0))   //第二圈左补线
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

  for (Ysite = 30; Ysite < 55; Ysite++) {    // 由于负压之后速度环需要调硬，所以斑马线的扫描为30到55 防止过硬的速度环导致小车直接刹车，没有过斑马线
    j = 0;
    for (Xsite = ImageDeal[Ysite].LeftBorder; Xsite < ImageDeal[Ysite].RightBorder; Xsite++) {
      if (Pixle[Ysite][Xsite] != Pixle[Ysite][Xsite + 1])  //检测到有黑白跳变点
        j++;
    }
    if (j > 10 /*&&rampnum==2*/) {
      ImageStatus.Road_type = Barn_in;
  //    ramp_flag = 1;                                       //检测到库就把这个标志位置1
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
      &&ImageStatus.Barn_Flag == 0)                         //第一次检测到车库  将标志位置为1
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
////入库补线  最后没用
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
////出库补线  最后没用
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
//  @brief          直线加速处理
//  @parameter      void
//  @time
//  @Author         MRCHEN
//-------------------------------------------------------------
uint16 Speed_Goal_max=190;
uint16 Speed_Goal_min=170;
void straight_speed(void)
{
    if(ImageStatus.straight_acc == 1)               //直道
        Speed_Goal = Speed_Goal_max;
    if(ImageStatus.straight_acc == 0)
        Speed_Goal = Speed_Goal_min;
    if(ImageStatus.Road_type == LeftCirque||ImageStatus.Road_type == RightCirque)
        Speed_Goal = Speed_Goal_min;
}

//用于加速的直道检测
float variance, variance_acc;  //方差
void Straightacc_Test(void)
{
    int sum = 0;
    for (Ysite = 55; Ysite > ImageStatus.OFFLine + 1; Ysite--)
    {
        sum += (ImageDeal[Ysite].Center - ImageStatus.MiddleLine) *(ImageDeal[Ysite].Center - ImageStatus.MiddleLine);
    }
    variance_acc = (float)sum / (54 - ImageStatus.OFFLine);
    length_max = len_maxget();
    if(length_max > 52  //  最长白列，通过判断赛道最大的宽度是否满足规定的区间 来判断是否为直道
    && ImageStatus.OFFLine <= 15 // 直道的前瞻一定很小
    && ImageStatus.Left_Line < 2  // 直道不允许有左丢边的情况
    && ImageStatus.Right_Line < 2 //  && ImageStatus.Road_type == 0// 直道不允许有右丢边的情况
    && abs((ImageStatus.Det_True-39)) <6)
        ImageStatus.straight_acc = 1;
    else
        ImageStatus.straight_acc = 0;
}

//计算一列的白列长度
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
//计算20~60列之间的最长白列长度
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
        //找左边十字特征
    for (Ysite = 54; Ysite > ImageStatus.OFFLine+2; Ysite--) {

        //十字底边的有边
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

        //十字中间的丢边
        if(ImageDeal[Ysite].IsLeftFind=='W'&&ImageDeal[Ysite-1].IsLeftFind=='W'&&leftmiddlen==0){
            while(ImageDeal[Ysite].IsLeftFind=='W'){
                leftmiddlen++;
                Ysite--;
            }
        }

        //十字上边的有边
        if(ImageDeal[Ysite].IsRightFind=='T'&&ImageDeal[Ysite-1].IsRightFind=='T'&&lefthighlen==0){
            while(ImageDeal[Ysite].IsRightFind=='T'){
                lefthighlen++;
                Ysite--;
            }
        }
    }
        //找右边十字特征
    for (Ysite = 54; Ysite > ImageStatus.OFFLine+2; Ysite--) {
        //十字底边的有边
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

        //十字底边的丢边
        if(ImageDeal[Ysite].IsRightFind=='W'&&ImageDeal[Ysite-1].IsRightFind=='W'&&rightmiddlen==0){
            while(ImageDeal[Ysite].IsRightFind=='W'){
                rightmiddlen++;
                Ysite--;
            }
        }

        //十字上边的有边
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

//  if (  (ImageStatus.Road_type == Forkin || ImageStatus.Road_type == Forkout))                                           //第一圈右补线
//  {
//      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--) {
//      ImageDeal[Ysite].Center = ImageDeal[Ysite].LeftBorder + buxianwide[Ysite]*0.5;}
//      //ImageDeal[Ysite].Wide = ImageDeal[Ysite].RightBorder -ImageDeal[Ysite].LeftBorder;  //宽度更新
//   //   Fit1(59,50);
//    }

  if (ImageStatus.Road_type==Cross_ture)   //第二圈左补线
  {
      for (Ysite = 58; Ysite > ImageStatus.OFFLine; Ysite--)
      {
      ImageDeal[Ysite].Center = ImageDeal[Ysite].RightBorder - buxianwide[Ysite]*0.5;
      ImageDeal[Ysite].LeftBorder=ImageDeal[Ysite].RightBorder - buxianwide[Ysite];
      }
      Fit1(59,50);
   }

}


/****元素检测*****/  //圆环 十字 车库 需要通过编码器积分自己跳出元素标志  而三叉只在一瞬间
                     //所以没检测到特征就直接此处跳出
uint8 Var_speed_start=0;//缓冲起步相关
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
        straight_speed();//速度处理
    }
    //圆环检测
//    if(ImageStatus.straight_acc == 0)//&& huan_start == 1)
//    {
        if(YH_flag == 0)
        {
            Element_Judgment_Left_Rings();           //左圆环检测
            Element_Judgment_Right_Rings();          //右圆环检测
        }
        else if(YH_flag == 1)
        {
            Element_Judgment_Left_Rings();           //左圆环检测
        }
        else if(YH_flag == 2)
        {
            Element_Judgment_Right_Rings();          //右圆环检测
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
/****出界处理********/
void Stop_Test(void)
{
    if(ImageStatus.Road_type == LeftCirque || ImageStatus.Road_type == RightCirque)
        return;
    if(ImageStatus.OFFLine >= 55)           //如果电磁很小并且可视距离基本没有就表示出界
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

void DrawLine()  //画边界  好调试
{
  uint8 i;
  for (i = 59; i > ImageStatus.OFFLine; i--) {
    Pixle[i][ImageDeal[i].LeftBorder + 2] = 0;  //移动两位便于观察
    Pixle[i][ImageDeal[i].RightBorder - 2] = 0;
    Pixle[i][ImageDeal[i].Center] = 0;
  }
}

/*****************误差按权重重新整定**********************/
void GetDet() {
  float DetTemp = 0;
  int TowPoint = 0;
  float SpeedGain = 0;
  float UnitAll = 0;

  SpeedGain=(SystemData.SpeedData.nowspeed - SystemData.SpeedData.MinSpeed) * 0.2 +0.5 ;//根据速度调整前瞻的因子   速度高于80  增益为负数  前瞻加长

    if (SpeedGain >= 3)
      SpeedGain = 3;
    else if (SpeedGain <= -1)
      SpeedGain = -1;

//    if ((ImageStatus.Road_type == RightCirque ||ImageStatus.Road_type == LeftCirque)&&ImageStatus.CirqueOff == 'F')
//    TowPoint = 23;                                                                      //圆环前瞻

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
    TowPoint = ImageStatus.TowPoint-SpeedGain;                                          //速度越快前瞻越长

  if (TowPoint < ImageStatus.OFFLine)
    TowPoint = ImageStatus.OFFLine + 1;

  if (TowPoint >= 49)
    TowPoint = 49;

  if ((TowPoint - 5) >= ImageStatus.OFFLine) {                                          //前瞻取设定前瞻还是可视距离  需要分情况讨论
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
    DetTemp =ImageStatus.Det_True;                                                     //如果是出现OFFLine>50情况，保持上一次的偏差值

  ImageStatus.Det_True = DetTemp;                                                      //此时的解算出来的平均图像偏差
//  if()
  ImageStatus.TowPoint_True = TowPoint;                                                //此时的前瞻
}


//--------------------------------------------------------------
//  @name           斑马线判断
//  @brief
//  @parameter      void
//-------------------------------------------------------------
int Zebras;   //斑马线积分
int Zebras_;    //堵转积分
uint8  banmaxian_on=0;
void Element_Judgment_Zebra()//
{
    if( ImageStatus.Road_type == LeftCirque  //防止出环标志位没加导致一直占用标志位
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
    compressimage();          //图像压缩 0.6ms
    ImageStatus.OFFLine = 2;  //这个值根据真实距离得到，必须进行限制
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

  }                     //边界与标志位初始化

 // K = Fit1_k(59-ImageStatus.OFFLine+10,10);

  Get01change_dajin();  //图像二值化    2.7ms
  //tft180_show_string(0,90,"che");
  //if(SystemData.clrcle_num!=2)
  Pixle_Filter();     //腐蚀         1.7ms}

  DrawLinesFirst();     //绘制底边      30us
  DrawLinesProcess();   //得到基本边线  8us
  Search_Border_OTSU(Pixle, LCDH, LCDW, LCDH - 2);//58行位底行

  /***元素识别*****/
  Element_Test();                   //5us
  /***元素识别*****/
  DrawExtensionLine();
  RouteFilter();        //中线滤波平滑 2us

  //斑马线
  if(Zebras<320)    //斑马线判断延时
      Zebras++;
      if(Zebras>300)
          if(ImageStatus.Road_type != LeftCirque
           &&ImageStatus.Road_type != RightCirque)
              Element_Judgment_Zebra();  //斑马线判断

  /***元素处理*****/
  Element_Handle();  // 3us
  /***元素处理*****/
  Stop_Test();           //出界保护   有两个  这个保护力度大
  GetDet();               //获取动态前瞻  并且计算图像偏差 3us

  //cpu1_get_err == 1;
     // Menu_key_set();

  //Stop_Test3();//2024年3月7日03:07:31

//  ImageStatus.Foresight = ((((ImageDeal[ImageStatus.OFFLine + 1].Center) +
//                             (ImageDeal[ImageStatus.OFFLine + 2].Center) +
//                             (ImageDeal[ImageStatus.OFFLine + 3].Center)) /3) -40);
//
//  ImageStatus.Det_all = (ImageStatus.Foresight + 40) - ImageDeal[54].Center;
//  ImageStatus.Det_all_k =(float)(ImageStatus.Det_all) / (ImageStatus.OFFLine + 2 - 54) * 30;
//  ImageStatus.Foresight = abs(ImageStatus.Foresight);
}
