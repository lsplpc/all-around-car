#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "Motor.h"
#include "Key.h"
#include "Serial.h"
#include "Encoder.h"
#include "PID.h"
#include <string.h>
#include <stdlib.h>
#include "CarControl.h"
#include "read.h"
void car_control_go (int8_t target_SpeedA,int8_t target_SpeedB,int8_t target_SpeedC,int8_t target_SpeedD);
uint8_t gw_gray_serial_read(void);//读不出来就看看这个

 int16_t SpeedA=0;
 int16_t SpeedB=0;
 int16_t SpeedC=0;
 int16_t SpeedD=0;
 float cha=0;
unsigned char Digtal;
unsigned char rx_buff[256]={0};//存储灰度数据

 uint8_t KeyNun;
 float Limit_value;
 PID playpid;
int main(void)
{ 
	SystemInit();
	delay_init(168);//放在开头
	Motor_Init();
	Key_Init();
	Serial_Init();//初始化USART
	read_Init();//初始化灰度
	Encoder_Init_TIM2();
	Encoder_Init_TIM4();
	Encoder_Init_TIM8();
	Encoder_Init_TIM1();
	Encoder_Init_TIM5();
	Encoder_Init_TIM9();
	CarControl_Init();
	PID_Init(&playpid, 3.5 , 0.1 , 0.2 , 100);
	Serial_SendString("可以了");

	 for(;;)
	{
		Digtal=gw_gray_serial_read();
		sprintf((char *)rx_buff,"Digtal %d-%d-%d-%d-%d-%d-%d-%d\r\n",(Digtal>>0)&0x01,(Digtal>>1)&0x01,(Digtal>>2)&0x01,(Digtal>>3)&0x01,(Digtal>>4)&0x01,(Digtal>>5)&0x01,(Digtal>>6)&0x01,(Digtal>>7)&0x01);
	    Serial_SendString((char *)rx_buff);
	    memset(rx_buff,0,256);
	    cha = xunji (Digtal);
		target_SpeedA=20;  target_SpeedB=20 ; target_SpeedC=20  ;target_SpeedD=20 ;//最大值在30附近25
		car_control_go (target_SpeedA+cha,target_SpeedB+cha,target_SpeedC-cha,target_SpeedD-cha);
		delay_ms(1);
	}
	 




}


void car_control_go (int8_t target_SpeedA,int8_t target_SpeedB,int8_t target_SpeedC,int8_t target_SpeedD)
{


     int encoder_countA = Read_EncoderA();
     int encoder_countB = Read_EncoderB();
	 int encoder_countC = -Read_EncoderC();
	 int encoder_countD = Read_EncoderF()*2;

//	 float Motor_Speed = (float)encoder_countA/30/13/4*1000;//(float)encoder_count：明确将整数转换为浮点型。
	 float Motor_SpeedA = (float)encoder_countA/30/13/4*1000;
	 float Motor_SpeedB = (float)encoder_countB/30/13/4*1000;
     float Motor_SpeedC = (float)encoder_countC/30/13/4*1000;
	 float Motor_SpeedD = (float)encoder_countD/30/13/4*1000;
	 
//	 target_Speed=key_contral ();(改变速度)
	 
//	 Speed = PID_Position_Calc(&playpid, target_Speed, Acttual_Speed);位置环
	
	SpeedA = PID_Incremental_Calc(&playpid,target_SpeedA, Motor_SpeedA);//速度环		
	SpeedB = PID_Incremental_Calc(&playpid,target_SpeedB, Motor_SpeedB);//速度环
	SpeedC = PID_Incremental_Calc(&playpid,target_SpeedC, Motor_SpeedC);//速度环
	SpeedD = PID_Incremental_Calc(&playpid,target_SpeedD, Motor_SpeedD);//速度环	
	
	 Motor_SetSpeedA(SpeedA);
	 Motor_SetSpeedB(SpeedB);
     Motor_SetSpeedC(SpeedC);
	 Motor_SetSpeedD(SpeedD);
	 
	 printf("pwmA:%d",SpeedA);
	 printf("pwmB:%d",SpeedB);
	 printf("pwmC:%d",SpeedC);
	 printf("pwmD:%d\r\n",SpeedD);

	 printf("target:%d",target_SpeedA);
	 printf("target:%d",target_SpeedB);
	 printf("target:%d",target_SpeedC);
	 printf("target:%d\r\n",target_SpeedD);
	 
	 
     printf("nowA:%.1f(rad)\r\n",Motor_SpeedA);
	 printf("nowB:%.1f(rad)\r\n",Motor_SpeedB);
	 printf("nowC:%.1f(rad)\r\n",Motor_SpeedC);
	 printf("nowD:%.1f(rad)\r\n",Motor_SpeedD);


}

uint8_t gw_gray_serial_read()
{
	uint8_t ret = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		/* 输出时钟下降沿 */
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(5);
		//避免GPIO翻转过快导致反应不及时
		ret |= GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) << i;

		/* 输出时钟上升沿,让传感器更新数据*/
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
	
		/* 延迟需要在5us左右 */
		delay_us(5);
	}
	
	return ret;
}


