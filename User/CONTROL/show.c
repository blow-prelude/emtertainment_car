#include "show.h"

void Show(void){
	
	memset(OLED_GRAM,0, 128*8*sizeof(u8));
	if (Mode == Normal_Mode){
	
//			OLED_ShowString(50,0,"Normal ");
//		if(PS2_ON_Flag==RC_ON)	
//		{
//			OLED_ShowString(0,10,"PS2       ");
//		}
//		else{
//			OLED_ShowString(0,10,"LINKING...");
//		}
		
//		// ��3����ʾ�ٶ�
//		if(PS2_ON_Flag==RC_ON){
//			OLED_ShowString(0,10,"PS2       ");
//		}
//		
//				else//��������ת���ٶ���ʾ����ת���ٶ�
//		{
//									OLED_ShowString(00,20,"SPEED:");
//			if( RC_Velocity<0)		OLED_ShowString(50,20,"-");
//			else					OLED_ShowString(50,20,"+");
//									OLED_ShowNumber(60,20,myabs(RC_Velocity),4,12);
//			if( RC_Turn_Velocity<0)		OLED_ShowString(94,20,"-");
//			else					OLED_ShowString(94,20,"+");
//									OLED_ShowNumber(106,20,myabs(RC_Turn_Velocity),3,12);
//			
//		}
//		
//		// ��4����ʾǰ���ٶȿ���
//		OLED_ShowString(0,30,"Move_X:");
//		OLED_ShowString(60,30,"Move_Z:");
//		// ��5����ʾ���pwm
//		OLED_ShowString(0,40,"A_PWM:");
//		OLED_ShowNumber(50,40,myabs(My_MotorA.Motor_Pwm),4,12);
//		OLED_ShowString(94,40,"B_PWM:");
//		OLED_ShowNumber(106,40,myabs(My_MotorB.Motor_Pwm),4,12);
//		
//		// ��6����ʾ����
//	if(Car_Num == Akm_Car){
//		OLED_ShowString(0,50,"AKM  ");
//	}
//	else {
//		OLED_ShowString(0,50,"BTANK");
//	}
//	
	} 
	
		// ��������ʾ��ȡ��ģ����
	OLED_ShowNumber(0,0,PS2_LX,3,12);
	OLED_ShowNumber(30,0,PS2_LY,3,12);
	OLED_ShowNumber(60,0,PS2_RX,3,12);
	OLED_ShowNumber(90,0,PS2_RY,3,12);

//	
//	// ��������ʾ�ٶȣ������ȣ�
//	OLED_ShowNumber(0,10,RC_Velocity,3,12);
//	OLED_ShowNumber(30,10,RC_Turn_Velocity,3,12);
//	
//	// ��������ʾ����
//	OLED_ShowNumber(0,20,Move_X*1000,4,12);
//	OLED_ShowNumber(50,20,-Move_Z,4,12);
////	if(++counter>=10000)
////		counter=0;
//	
//	// �Ѽ���������ٶ�ֵ�Ŵ�100��
//	OLED_ShowNumber(0,30,My_MotorB.Motor_Velocity*100,3,12);
//	OLED_ShowNumber(50,30,My_MotorA.Motor_Velocity*100,3,12);
	
	// ��5����ʾ�����pwm��
	 OLED_ShowNumber(0,40,My_MotorA.Motor_Pwm,4,12);
	 OLED_ShowNumber(60,40,My_MotorB.Motor_Pwm,4,12);
	 
	 // ��4����ʾ�����pwm��
	  OLED_ShowNumber(0,30,Servo_PWM,4,12);
		
	// ��3����ʾ�ٶȣ������ȣ�
	OLED_ShowNumber(0,20,RC_Velocity,3,12);
	OLED_ShowNumber(40,20,RC_Turn_Velocity,3,12);
	
	// ��2����ʾ��ȡ�İ���
	OLED_ShowNumber(50,10,PS2_KEY,2,12);
	OLED_ShowString(0,10,"KEY:");

	// ˢ��
	OLED_Refresh_Gram();	
	
	
}


u16 myabs(int Input)
{
	int Output;
	if(Input > 0)
		Output = Input;
	else
		Output = -Input;
	return Output;
}
