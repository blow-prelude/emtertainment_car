#ifndef __CONTROL_H
#define __CONTROL_H

#include "Header.h"
//PWM限制最大最小值
#define PWM_MAX  6900
#define PWM_MIN  -6900

#define Default_Velocity					900			//默认遥控速度，单位mm/s
#define Default_Turn_Bias					Pi/4			//默认遥控速度，单位度/s
#define PS2_Turn_Angle						Pi/4		//阿克曼车手柄默认转向角度，单位rad

//小车各模式定义
#define Normal_Mode							0


//指示遥控控制的开关
#define RC_ON								1	
#define RC_OFF								0
//遥控控制前后速度最大值
#define MAX_RC_Velocity						1230
//遥控控制转向速度最大值
#define	MAX_RC_Turn_Bias					1
//遥控控制前后速度最小值
#define MINI_RC_Velocity					210
//遥控控制转向速度最小值
#define	MINI_RC_Turn_Velocity			    Pi/20

//前进加减速幅度值，每次遥控加减的步进值
#define X_Step								25
//转弯加减速幅度值
#define Z_Step								0.1

//车轮直径
#define Diff_Car_Wheel_diameter				0.0670f			//差速车和阿克曼车，单位m
#define Small_Tank_WheelDiameter			0.0430f			//小履带车
#define Big_Tank_WheelDiameter				0.0440f			//大履带车

//车轮轮距
#define Diff_wheelspacing					0.177			//差速车轮距
#define Akm_wheelspacing					0.162		//阿克曼车轮距
#define Small_Tank_wheelspacing				0.1350		//小履带车轮距
#define Big_Tank_wheelspacing				0.2330			//大履带车轮距

#define Akm_axlespacing           			0.144f			//阿克曼车轴距
#define Diff_axlespacing                    0.155f           //差速车轴距


#define Gear_Ratio							30.0f			//电机的减速比


#define Pi									3.14159265358979f	//圆周率
#define Angle_To_Rad						57.295779513f	//角度制转弧度制，除以这个参数
#define Frequency							200.0f			//每5ms读取一次编码器的值
#define SERVO_INIT 							1600  			//舵机零点PWM值






typedef struct  
{
	float Motor_Pwm;     		//电机PWM数值，控制电机实时速度
	float Motor_Velocity; 	 		//目标电机速度值
}My_Motor_parameter;

extern volatile float Move_X,Move_Z;						//目标速度和目标转向速度
extern float PWM_Left,PWM_Right;					//左右电机PWM值
extern volatile float RC_Velocity,RC_Turn_Velocity;			//遥控控制的速度
extern u8 Mode;								//模式选择，默认是普通的控制模式

extern int Servo_PWM;					//阿克曼舵机相关变量

extern My_Motor_parameter My_MotorA,My_MotorB;    // 电机

void PS2_Control(void);
int TIMING_TIM_IRQHandler(void);

void Car_Perimeter_Init(void);     // 计算轮子的周长
void Get_Target_Encoder(float Vx,float Vz);
void Get_Motor_PWM(void);

float target_limit_float(float insert,float low,float high);
int target_limit_int(int insert,int low,int high);
float PWM_Limit(float IN,float max,float min);

#endif