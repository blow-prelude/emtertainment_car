#ifndef __CONTROL_H
#define __CONTROL_H

#include "Header.h"
//PWM���������Сֵ
#define PWM_MAX  6900
#define PWM_MIN  -6900

#define Default_Velocity					350			//Ĭ��ң���ٶȣ���λmm/s
#define Default_Turn_Bias					Pi/4			//Ĭ��ң���ٶȣ���λ��/s
#define PS2_Turn_Angle						Pi/4		//���������ֱ�Ĭ��ת��Ƕȣ���λrad

//С����ģʽ����
#define Normal_Mode							0


//ָʾң�ؿ��ƵĿ���
#define RC_ON								1	
#define RC_OFF								0
//ң�ؿ���ǰ���ٶ����ֵ
#define MAX_RC_Velocity						800
//ң�ؿ���ת���ٶ����ֵ
#define	MAX_RC_Turn_Bias					1
//ң�ؿ���ǰ���ٶ���Сֵ
#define MINI_RC_Velocity					210
//ң�ؿ���ת���ٶ���Сֵ
#define	MINI_RC_Turn_Velocity			    Pi/20

//ǰ���Ӽ��ٷ���ֵ��ÿ��ң�ؼӼ��Ĳ���ֵ
#define X_Step								25
//ת��Ӽ��ٷ���ֵ
#define Z_Step								0.1

//����ֱ��
#define Diff_Car_Wheel_diameter				0.0670f			//���ٳ��Ͱ�����������λm
#define Small_Tank_WheelDiameter			0.0430f			//С�Ĵ���
#define Big_Tank_WheelDiameter				0.0440f			//���Ĵ���

//�����־�
#define Diff_wheelspacing					0.177			//���ٳ��־�
#define Akm_wheelspacing					0.162		//���������־�
#define Small_Tank_wheelspacing				0.1350		//С�Ĵ����־�
#define Big_Tank_wheelspacing				0.2330			//���Ĵ����־�

#define Akm_axlespacing           			0.144f			//�����������
#define Diff_axlespacing                    0.155f           //���ٳ����


#define Gear_Ratio							30.0f			//����ļ��ٱ�


#define Pi									3.14159265358979f	//Բ����
#define Angle_To_Rad						57.295779513f	//�Ƕ���ת�����ƣ������������
#define Frequency							200.0f			//ÿ5ms��ȡһ�α�������ֵ
#define SERVO_INIT 							1500  			//������PWMֵ


//����ٶȿ�����ز����ṹ��
typedef struct  
{
	float Current_Encoder;     	//��������ֵ����ȡ���ʵʱ�ٶ�
	float Motor_Pwm;     		//���PWM��ֵ�����Ƶ��ʵʱ�ٶ�
	float Target_Encoder;  		//���Ŀ��������ٶ�ֵ�����Ƶ��Ŀ���ٶ�
	float Velocity; 	 		//����ٶ�ֵ
}Motor_parameter;



extern float Move_X,Move_Z;						//Ŀ���ٶȺ�Ŀ��ת���ٶ�
extern float PWM_Left,PWM_Right;					//���ҵ��PWMֵ
extern float RC_Velocity,RC_Turn_Velocity;			//ң�ؿ��Ƶ��ٶ�
extern u8 Mode;								//ģʽѡ��Ĭ������ͨ�Ŀ���ģʽ
extern Motor_parameter MotorA,MotorB;				//���ҵ����ر���
extern int Servo_PWM;					//�����������ر���


void PS2_Control(void);
int TIMING_TIM_IRQHandler(void);

void Car_Perimeter_Init(void);     // �������ӵ��ܳ�
#endif