#include "show.h"

void Show(void){
	memset(OLED_GRAM,0, 128*8*sizeof(u8));
	if (Mode == Normal_Mode){
			OLED_ShowString(50,0,"Normal ");
		if(PS2_ON_Flag==RC_ON)	
		{
			OLED_ShowString(0,10,"PS2       ");
		}
		else{
			OLED_ShowString(0,10,"LINKING...");
		}
		
		// 第3行显示速度
		if(PS2_ON_Flag==RC_ON){
			OLED_ShowString(0,10,"PS2       ");
		}
		
				else//其他车型转向速度显示差速转向速度
		{
									OLED_ShowString(00,20,"SPEED:");
			if( RC_Velocity<0)		OLED_ShowString(50,20,"-");
			else					OLED_ShowString(50,20,"+");
									OLED_ShowNumber(60,20,myabs(RC_Velocity),4,12);
			if( RC_Turn_Velocity<0)		OLED_ShowString(94,20,"-");
			else					OLED_ShowString(94,20,"+");
									OLED_ShowNumber(106,20,myabs(RC_Turn_Velocity),3,12);
			
		}
		
		// 第6行显示车型
	if(Car_Num == Akm_Car){
		OLED_ShowString(0,50,"AKM  ");
	}
	else {
		OLED_ShowString(0,50,"BTANK");
	}
	
	} 
	
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
