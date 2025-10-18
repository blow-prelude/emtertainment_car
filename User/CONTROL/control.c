#include "control.h"

float Move_X =0,Move_Z = 0;						//Ŀ���ٶȺ�Ŀ��ת���ٶ�
float PWM_Left,PWM_Right;					//���ҵ��PWMֵ
float RC_Velocity,RC_Turn_Velocity;			//ң�ؿ��Ƶ��ٶ�
u8 Mode = 0;								//ģʽѡ��Ĭ������ͨ�Ŀ���ģʽ
Motor_parameter MotorA,MotorB;				//���ҵ����ر���
int Servo_PWM = SERVO_INIT;					//�����������ر���


// 5ms�Ķ�ʱ���жϿ��ƺ���
int TIMING_TIM_IRQHandler(void){
	if(TIM_GetITStatus( TIMING_TIM, TIM_IT_Update) != RESET ){
		TIM_ClearITPendingBit(TIMING_TIM , TIM_IT_Update);
		
		if(Mode == Normal_Mode){
			if(PS2_ON_Flag == RC_ON)							//�����ֱ�����ʱ�����Ȱ�start������Ȼ��������ҡ��ֱ������ PS2 ����
				PS2_Control();
		}
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
			if((RC_Velocity += X_Step)>MAX_RC_Velocity)				//ǰ������ٶ�1230
				RC_Velocity = MAX_RC_Velocity;

		}
	}
	else if(PS2_KEY == PSB_R1) 					//������1������
	{
		if((++Key2_Count) == 20)
		{
			PS2_KEY = 0;
			Key2_Count = 0;
			if((RC_Velocity -= X_Step)<MINI_RC_Velocity)			//ǰ����С�ٶ�210
				RC_Velocity = MINI_RC_Velocity;
			
			
		}
	}
	else
		Key2_Count = 0,Key2_Count = 0;			//��ȡ�������������¼���
	Move_X=Move_X/1000;  Move_Z=-Move_Z;
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
