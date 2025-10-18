/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：V1.0
修改时间：2023-03-02

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update：2023-03-02

All rights reserved
***********************************************/
#include "Header.h"
u8 Car_Num;
u8 Flag_Show ;					//显示标志位，默认开启，长按切换到上位机模式，此时关闭

float Perimeter;       // 轮子的周长
float Wheelspacing;    // 轮子的间距
u8 PS2_ON_Flag = 0;		//默认所有方式不控制

int main(void)
{
	Car_Num = Akm_Car; // 设置为阿克曼车型
	
		// 中断优先组分级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		// 关闭JTAG接口并且打开SWD接口
	JTAG_Set(JTAG_SWD_DISABLE);
	JTAG_Set(SWD_ENABLE);
		// OLED初始化
	OLED_Init();
		// PS2初始化
	PS2_Init();
	PS2_SetInit();	
		// 电机pwm初始化
	Motor_Init(7199,0);
	
	if (Car_Num==Akm_Car){
	// 初始化舵机
		Servo_Init(9999,71);
	// 初始化轮子周长和轮距	
		Car_Perimeter_Init();
		// 初始化定时器5？？ 5ms的中断控制
		TIMING_TIM_Init(7199,49);	
	}
	while(1){
		// 读取ps2的值
		PS2_Read();
		// 显示在oled屏上
		Show();	
	}
}

/***********************************END OF FILE********************************/

