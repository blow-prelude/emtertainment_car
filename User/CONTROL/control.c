#include "control.h"

float Move_X =0,Move_Z = 0;						//目标速度和目标转向速度
float PWM_Left,PWM_Right;					//左右电机PWM值
float RC_Velocity,RC_Turn_Velocity;			//遥控控制的速度
u8 Mode = 0;								//模式选择，默认是普通的控制模式
Motor_parameter MotorA,MotorB;				//左右电机相关变量
int Servo_PWM = SERVO_INIT;					//阿克曼舵机相关变量


// 5ms的定时器中断控制函数
int TIMING_TIM_IRQHandler(void){
	if(TIM_GetITStatus( TIMING_TIM, TIM_IT_Update) != RESET ){
		TIM_ClearITPendingBit(TIMING_TIM , TIM_IT_Update);
		
		if(Mode == Normal_Mode){
			if(PS2_ON_Flag == RC_ON)							//开启手柄控制时，需先按start按键，然后上拉左摇杆直到出现 PS2 字样
				PS2_Control();
		}
	}
	return 0;
}


// ps2手柄控制
void PS2_Control(void)
{
	int LY,RX;									//手柄ADC的值
	int Threshold=20; 							//阈值，忽略摇杆小幅度动作
	static u8 Key1_Count = 0,Key2_Count = 0;	//用于控制读取摇杆的速度
	//转化为128到-128的数值
	LY=-(PS2_LY-128);//左边Y轴控制前进后退
	RX=-(PS2_RX-128);//右边X轴控制转向

	if(LY>-Threshold&&LY<Threshold)	LY=0;
	if(RX>-Threshold&&RX<Threshold)	RX=0;		//忽略摇杆小幅度动作
	
	Move_X = (RC_Velocity/128)*LY;				//速度控制，力度表示速度大小
	if(Car_Num == Akm_Car)						//阿克曼车转向控制，力度表示转向角度
		Move_Z = -(RC_Turn_Velocity/128)*RX;	

	if (PS2_KEY == PSB_L1) 					 	//按下左1键加速（按键在顶上）
	{	
		if((++Key1_Count) == 20)				//调节按键反应速度
		{
			PS2_KEY = 0;
			Key1_Count = 0;
			if((RC_Velocity += X_Step)>MAX_RC_Velocity)				//前进最大速度1230
				RC_Velocity = MAX_RC_Velocity;

		}
	}
	else if(PS2_KEY == PSB_R1) 					//按下右1键减速
	{
		if((++Key2_Count) == 20)
		{
			PS2_KEY = 0;
			Key2_Count = 0;
			if((RC_Velocity -= X_Step)<MINI_RC_Velocity)			//前后最小速度210
				RC_Velocity = MINI_RC_Velocity;
			
			
		}
	}
	else
		Key2_Count = 0,Key2_Count = 0;			//读取到其他按键重新计数
	Move_X=Move_X/1000;  Move_Z=-Move_Z;
}


// 计算轮子的周长
void Car_Perimeter_Init(void)
{
	if(Car_Num == Diff_Car||Car_Num == Akm_Car)
	{
		Perimeter = Diff_Car_Wheel_diameter*Pi;
		Wheelspacing = Diff_wheelspacing;
	}		
	else if(Car_Num == Small_Tank_Car)
	{
		Perimeter = Small_Tank_WheelDiameter*Pi;
		Wheelspacing = Small_Tank_wheelspacing;
	}
	else
	{
		Perimeter = Big_Tank_WheelDiameter*Pi;
		Wheelspacing = Big_Tank_wheelspacing;
	}
}
