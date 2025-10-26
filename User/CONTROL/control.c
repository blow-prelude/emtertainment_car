#include "control.h"

volatile float Move_X =0,Move_Z = 0;						//Ŀ���ٶȺ�Ŀ��ת���ٶ�
float PWM_Left,PWM_Right;					//���ҵ��PWMֵ
volatile float RC_Velocity,RC_Turn_Velocity;			//ң�ؿ��Ƶ��ٶ�
u8 Mode = 0;								//ģʽѡ��Ĭ������ͨ�Ŀ���ģʽ

int Servo_PWM = SERVO_INIT;					//�����������ر���

My_Motor_parameter My_MotorA,My_MotorB;
// 5m�Ķ�ʱ���жϿ��ƺ���
int TIMING_TIM_IRQHandler(void){
	if(TIM_GetITStatus( TIMING_TIM, TIM_IT_Update) != RESET ){
		TIM_ClearITPendingBit(TIMING_TIM , TIM_IT_Update);
		
		if(Mode == Normal_Mode){
			if(PS2_ON_Flag == RC_ON)							//�����ֱ�����ʱ�����Ȱ�start������Ȼ��������ҡ��ֱ������ PS2 ����
				PS2_Control();
		}
		
		Get_Target_Encoder(Move_X,Move_Z);							//�˶�ѧ���⣬ת����Ŀ���ٶ�
		Get_Motor_PWM();   // ��Ŀ���ٶ�ת����PWM
		
		Set_Pwm(-My_MotorA.Motor_Pwm,My_MotorB.Motor_Pwm);    // �������
		
	}
	return 0;
}


// ps2�ֱ�����
void PS2_Control(void)
{

	int LY,RX;									//�ֱ�ADC��ֵ
	int Threshold=20; 							//��ֵ������ҡ��С���ȶ���
	static u8 Key1_Count = 0,Key2_Count = 0;	//���ڿ��ƶ�ȡҡ�˵��ٶ�
	//ת��Ϊ128��-128����ֵ
	LY=-(PS2_LY-128);//���Y�����ǰ������
	RX=-(PS2_RX-128);//�ұ�X�����ת��

	if(LY>-Threshold&&LY<Threshold)	LY=0;
	if(RX>-Threshold&&RX<Threshold)	RX=0;		//����ҡ��С���ȶ���
	
	Move_X = (RC_Velocity/128)*LY;				//�ٶȿ��ƣ����ȱ�ʾ�ٶȴ�С
	if(Car_Num == Akm_Car)						//��������ת����ƣ����ȱ�ʾת��Ƕ�
		Move_Z = -(RC_Turn_Velocity/128)*RX;	

	if (PS2_KEY == PSB_L1) 					 	//������1�����٣������ڶ��ϣ�
	{	
		if((++Key1_Count) == 20)				//���ڰ�����Ӧ�ٶ�
		{
			PS2_KEY = 0;
			Key1_Count = 0;
			RC_Velocity += X_Step;
			if(RC_Velocity >MAX_RC_Velocity)				//ǰ������ٶ�1230
				RC_Velocity = MAX_RC_Velocity;

		}
	}
	else if(PS2_KEY == PSB_R1) 					//������1������
	{
		if((++Key2_Count) == 20)
		{
			PS2_KEY = 0;
			Key2_Count = 0;
			RC_Velocity -= X_Step;
			if(RC_Velocity <MINI_RC_Velocity)			//ǰ����С�ٶ�210
				RC_Velocity = MINI_RC_Velocity;
			
			
		}
	}
	else
		Key2_Count = 0,Key2_Count = 0;			//��ȡ�������������¼���
	Move_X=Move_X/1000.0;  Move_Z=-Move_Z;
	if(++counter>3000)
		counter=0;
}


// �������ӵ��ܳ�
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






// �޷�����
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
	float amplitude=3.5f; //Wheel target speed limit //����Ŀ���ٶ��޷�
	Move_X = target_limit_float(Move_X,-1.2,1.2);
	Move_Z = target_limit_float(Move_Z,-Pi/3,Pi/3);
	if(Car_Num==Akm_Car)							//��������
	{
		//Ackerman car specific related variables //������С��ר����ر���
			float R, ratio=636.62, AngleR, Angle_Servo;
			
			// For Ackerman small car, Vz represents the front wheel steering Angle
			//���ڰ�����С��Vz������ǰ��ת��Ƕ�
			AngleR=Vz;
//			R=Akm_axlespacing/tan(AngleR)-0.5f*Akm_wheelspacing;
		// ���������ְ뾶
			float R_center = Akm_axlespacing / tan(AngleR); // �������ĵ�ת��뾶
			float R_left  = R_center - 0.5f * Akm_wheelspacing;
			float R_right = R_center + 0.5f * Akm_wheelspacing;
			// Front wheel steering Angle limit (front wheel steering Angle controlled by steering engine), unit: rad
			//ǰ��ת��Ƕ��޷�(�������ǰ��ת��Ƕ�)����λ��rad
			AngleR=target_limit_float(AngleR,-0.32f,0.32f);
			//Inverse kinematics //�˶�ѧ���
			if(AngleR!=0)
			{
//				My_MotorA.Motor_Velocity = Vx*(R-0.081f)/R;
//				My_MotorB.Motor_Velocity = Vx*(R+0.081f)/R;	
				
				    My_MotorB.Motor_Velocity = Vx * R_right / R_center;  // ����A������
					My_MotorA.Motor_Velocity = Vx * R_left / R_center;   // ����B������
			}
			else 
			{
				My_MotorB.Motor_Velocity = Vx;
				My_MotorA.Motor_Velocity = Vx;
			}

			// The PWM value of the servo controls the steering Angle of the front wheel
			//���PWMֵ���������ǰ��ת��Ƕ�
			Angle_Servo = -0.628f*pow(AngleR, 3) + 1.269f*pow(AngleR, 2) - 1.772f*AngleR + 1.573f;
			Servo_PWM=SERVO_INIT + (Angle_Servo - 1.572f)*ratio;

			
			//Wheel (motor) target speed limit //����(���)Ŀ���ٶ��޷�
			My_MotorA.Motor_Velocity=target_limit_float(My_MotorA.Motor_Velocity,-amplitude,amplitude); 
			My_MotorB.Motor_Velocity=target_limit_float(My_MotorB.Motor_Velocity,-amplitude,amplitude); 
			Servo_PWM=target_limit_int(Servo_PWM,800,2200);	//Servo PWM value limit //���PWMֵ�޷�
	}
 
	

}



void Get_Motor_PWM()
{
  My_MotorA.Motor_Pwm=Map_V2Pwm(My_MotorA.Motor_Velocity);	
	My_MotorB.Motor_Pwm=Map_V2Pwm(My_MotorB.Motor_Velocity);	

	
	// �޷�
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