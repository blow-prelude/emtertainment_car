/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2023-03-02

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2023-03-02

All rights reserved
***********************************************/
#include "Header.h"
u8 Car_Num;
u8 Flag_Show ;					//��ʾ��־λ��Ĭ�Ͽ����������л�����λ��ģʽ����ʱ�ر�

float Perimeter;       // ���ӵ��ܳ�
float Wheelspacing;    // ���ӵļ��
u8 PS2_ON_Flag = 0;		//Ĭ�����з�ʽ������

int main(void)
{
	Car_Num = Akm_Car; // ����Ϊ����������
	
		// �ж�������ּ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		// �ر�JTAG�ӿڲ��Ҵ�SWD�ӿ�
	JTAG_Set(JTAG_SWD_DISABLE);
	JTAG_Set(SWD_ENABLE);
		// OLED��ʼ��
	OLED_Init();
		// PS2��ʼ��
	PS2_Init();
	PS2_SetInit();	
		// ���pwm��ʼ��
	Motor_Init(7199,0);
	
	if (Car_Num==Akm_Car){
	// ��ʼ�����
		Servo_Init(9999,71);
	// ��ʼ�������ܳ����־�	
		Car_Perimeter_Init();
		// ��ʼ����ʱ��5���� 5ms���жϿ���
		TIMING_TIM_Init(7199,49);	
	}
	while(1){
		// ��ȡps2��ֵ
		PS2_Read();
		// ��ʾ��oled����
		Show();	
	}
}

/***********************************END OF FILE********************************/

