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
		
//		// 第3行显示速度
//		if(PS2_ON_Flag==RC_ON){
//			OLED_ShowString(0,10,"PS2       ");
//		}
//		
//				else//其他车型转向速度显示差速转向速度
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
//		// 第4行显示前进速度控制
//		OLED_ShowString(0,30,"Move_X:");
//		OLED_ShowString(60,30,"Move_Z:");
//		// 第5行显示电机pwm
//		OLED_ShowString(0,40,"A_PWM:");
//		OLED_ShowNumber(50,40,myabs(My_MotorA.Motor_Pwm),4,12);
//		OLED_ShowString(94,40,"B_PWM:");
//		OLED_ShowNumber(106,40,myabs(My_MotorB.Motor_Pwm),4,12);
//		
//		// 第6行显示车型
//	if(Car_Num == Akm_Car){
//		OLED_ShowString(0,50,"AKM  ");
//	}
//	else {
//		OLED_ShowString(0,50,"BTANK");
//	}
//	
	} 
	
		// 第三行显示读取的模拟量
	OLED_ShowNumber(0,0,PS2_LX,3,12);
	OLED_ShowNumber(30,0,PS2_LY,3,12);
	OLED_ShowNumber(60,0,PS2_RX,3,12);
	OLED_ShowNumber(90,0,PS2_RY,3,12);

//	
//	// 第四行显示速度（灵敏度）
//	OLED_ShowNumber(0,10,RC_Velocity,3,12);
//	OLED_ShowNumber(30,10,RC_Turn_Velocity,3,12);
//	
//	// 第五行显示力度
//	OLED_ShowNumber(0,20,Move_X*1000,4,12);
//	OLED_ShowNumber(50,20,-Move_Z,4,12);
////	if(++counter>=10000)
////		counter=0;
//	
//	// 把计算出来的速度值放大100倍
//	OLED_ShowNumber(0,30,My_MotorB.Motor_Velocity*100,3,12);
//	OLED_ShowNumber(50,30,My_MotorA.Motor_Velocity*100,3,12);
	
	// 第5行显示电机的pwm波
	 OLED_ShowNumber(0,40,My_MotorA.Motor_Pwm,4,12);
	 OLED_ShowNumber(60,40,My_MotorB.Motor_Pwm,4,12);
	 
	 // 第4行显示舵机的pwm波
	  OLED_ShowNumber(0,30,Servo_PWM,4,12);
		
	// 第3行显示速度（灵敏度）
	OLED_ShowNumber(0,20,RC_Velocity,3,12);
	OLED_ShowNumber(40,20,RC_Turn_Velocity,3,12);
	
	// 第2行显示读取的按键
	OLED_ShowNumber(50,10,PS2_KEY,2,12);
	OLED_ShowString(0,10,"KEY:");

	// 刷新
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
