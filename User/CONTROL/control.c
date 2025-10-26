#include "control.h"

volatile float Move_X =0,Move_Z = 0;						//目标速度和目标转向速度
float PWM_Left,PWM_Right;					//左右电机PWM值
volatile float RC_Velocity,RC_Turn_Velocity;			//遥控控制的速度
u8 Mode = 0;								//模式选择，默认是普通的控制模式

int Servo_PWM = SERVO_INIT;					//阿克曼舵机相关变量

My_Motor_parameter My_MotorA,My_MotorB;
// 5m的定时器中断控制函数
int TIMING_TIM_IRQHandler(void){
	if(TIM_GetITStatus( TIMING_TIM, TIM_IT_Update) != RESET ){
		TIM_ClearITPendingBit(TIMING_TIM , TIM_IT_Update);
		
		if(Mode == Normal_Mode){
			if(PS2_ON_Flag == RC_ON)							//开启手柄控制时，需先按start按键，然后上拉左摇杆直到出现 PS2 字样
				PS2_Control();
		}
		
		Get_Target_Encoder(Move_X,Move_Z);							//运动学逆解解，转换成目标速度
		Get_Motor_PWM();   // 将目标速度转化成PWM
		
		Set_Pwm(-My_MotorA.Motor_Pwm,My_MotorB.Motor_Pwm);    // 驱动电机
		
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
			RC_Velocity += X_Step;
			if(RC_Velocity >MAX_RC_Velocity)				//前进最大速度1230
				RC_Velocity = MAX_RC_Velocity;

		}
	}
	else if(PS2_KEY == PSB_R1) 					//按下右1键减速
	{
		if((++Key2_Count) == 20)
		{
			PS2_KEY = 0;
			Key2_Count = 0;
			RC_Velocity -= X_Step;
			if(RC_Velocity <MINI_RC_Velocity)			//前后最小速度210
				RC_Velocity = MINI_RC_Velocity;
			
			
		}
	}
	else
		Key2_Count = 0,Key2_Count = 0;			//读取到其他按键重新计数
	Move_X=Move_X/1000.0;  Move_Z=-Move_Z;
	if(++counter>3000)
		counter=0;
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






// 限幅函数
float target_limit_float(float insert,float low,float high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;	
}

int target_limit_int(int insert,int low,int high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;	
}



void Get_Target_Encoder(float Vx,float Vz)
{
	float amplitude=3.5f; //Wheel target speed limit //车轮目标速度限幅
	Move_X = target_limit_float(Move_X,-1.2,1.2);
	Move_Z = target_limit_float(Move_Z,-Pi/3,Pi/3);
	if(Car_Num==Akm_Car)							//阿克曼车
	{
		//Ackerman car specific related variables //阿克曼小车专用相关变量
			float R, ratio=636.62, AngleR, Angle_Servo;
			
			// For Ackerman small car, Vz represents the front wheel steering Angle
			//对于阿克曼小车Vz代表右前轮转向角度
			AngleR=Vz;
//			R=Akm_axlespacing/tan(AngleR)-0.5f*Akm_wheelspacing;
		// 区分左右轮半径
			float R_center = Akm_axlespacing / tan(AngleR); // 车体中心的转弯半径
			float R_left  = R_center - 0.5f * Akm_wheelspacing;
			float R_right = R_center + 0.5f * Akm_wheelspacing;
			// Front wheel steering Angle limit (front wheel steering Angle controlled by steering engine), unit: rad
			//前轮转向角度限幅(舵机控制前轮转向角度)，单位：rad
			AngleR=target_limit_float(AngleR,-0.32f,0.32f);
			//Inverse kinematics //运动学逆解
			if(AngleR!=0)
			{
//				My_MotorA.Motor_Velocity = Vx*(R-0.081f)/R;
//				My_MotorB.Motor_Velocity = Vx*(R+0.081f)/R;	
				
				    My_MotorB.Motor_Velocity = Vx * R_right / R_center;  // 假设A是右轮
					My_MotorA.Motor_Velocity = Vx * R_left / R_center;   // 假设B是左轮
			}
			else 
			{
				My_MotorB.Motor_Velocity = Vx;
				My_MotorA.Motor_Velocity = Vx;
			}

			// The PWM value of the servo controls the steering Angle of the front wheel
			//舵机PWM值，舵机控制前轮转向角度
			Angle_Servo = -0.628f*pow(AngleR, 3) + 1.269f*pow(AngleR, 2) - 1.772f*AngleR + 1.573f;
			Servo_PWM=SERVO_INIT + (Angle_Servo - 1.572f)*ratio;

			
			//Wheel (motor) target speed limit //车轮(电机)目标速度限幅
			My_MotorA.Motor_Velocity=target_limit_float(My_MotorA.Motor_Velocity,-amplitude,amplitude); 
			My_MotorB.Motor_Velocity=target_limit_float(My_MotorB.Motor_Velocity,-amplitude,amplitude); 
			Servo_PWM=target_limit_int(Servo_PWM,800,2200);	//Servo PWM value limit //舵机PWM值限幅
	}
 
	

}



void Get_Motor_PWM()
{
  My_MotorA.Motor_Pwm=Map_V2Pwm(My_MotorA.Motor_Velocity);	
	My_MotorB.Motor_Pwm=Map_V2Pwm(My_MotorB.Motor_Velocity);	

	
	// 限幅
	My_MotorA.Motor_Pwm = PWM_Limit(My_MotorA.Motor_Pwm,PWM_MAX,PWM_MIN);
	My_MotorB.Motor_Pwm = PWM_Limit(My_MotorB.Motor_Pwm,PWM_MAX,PWM_MIN);
}


float PWM_Limit(float IN,float max,float min)
{
	float OUT = IN;
	if(OUT>max) OUT = max;
	if(OUT<min) OUT = min;
	return OUT;
}