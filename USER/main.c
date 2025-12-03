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

void car_control_go (int8_t target_SpeedA,int8_t target_SpeedB,int8_t target_SpeedC,int8_t target_SpeedD);
 int8_t SpeedA=0;
 int8_t SpeedB=0;
 int8_t SpeedC=0;
 int8_t SpeedD=0;

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
	Encoder_Init_TIM2();
	Encoder_Init_TIM4();
	Encoder_Init_TIM8();
	Encoder_Init_TIM1();
	Encoder_Init_TIM5();
	Encoder_Init_TIM9();
	CarControl_Init();
	PID_Init(&playpid, 0.7 , 0.1 , 0.1 , 100);
	Serial_SendString("可以了");
	 
while(1)
 {  
	Parse_KeyCmd();
    car_control_go (target_SpeedA,target_SpeedB,target_SpeedC,target_SpeedD);
    delay_ms(100);//0.1秒

 }

 

}

/*int key_contral (void)
{
KeyNun = Key_GetNum();
	 if(KeyNun==1)
	 {
	     target_Speed+=20;
	 
		 if(target_Speed>100)
		 {
			 target_Speed=-100;
		 }
		 
	 }

 return target_Speed;
}	*/

void car_control_go (int8_t target_SpeedA,int8_t target_SpeedB,int8_t target_SpeedC,int8_t target_SpeedD)
{


     int encoder_countA = Read_EncoderA();
     int encoder_countB = Read_EncoderB();
	 int encoder_countC = Read_EncoderC();
	 int encoder_countD = Read_EncoderF();

//	 float Motor_Speed = (float)encoder_countA/30/13/4*10;//(float)encoder_count：明确将整数转换为浮点型。
	 float Motor_SpeedA = (float)encoder_countA;
	 float Motor_SpeedB = (float)encoder_countB;
     float Motor_SpeedC = (float)encoder_countC;
	 float Motor_SpeedD = (float)encoder_countD;
	 
//	 target_Speed=key_contral ();(改变速度)
	 
//	 Speed = PID_Position_Calc(&playpid, target_Speed, Acttual_Speed);位置环
	
	SpeedA = PID_Incremental_Calc(&playpid,target_SpeedA, Motor_SpeedA);//速度环		
	SpeedB = PID_Incremental_Calc(&playpid,target_SpeedB, Motor_SpeedB);//速度环
	SpeedC = PID_Incremental_Calc(&playpid,target_SpeedC, Motor_SpeedC);//速度环
	SpeedD = PID_Incremental_Calc(&playpid,target_SpeedD, Motor_SpeedD);//速度环	
	
	 Motor_SetSpeedA(SpeedA/2.3985f);
	 Motor_SetSpeedB(SpeedB/2.3985f);
     Motor_SetSpeedC(SpeedC/2.3985f);
	 Motor_SetSpeedD(SpeedD/2.3985f);
	 
	 printf("pwmA:%d",SpeedA);
	 printf("pwmB:%d",SpeedB);
	 printf("pwmC:%d",SpeedC);
	 printf("pwmD:%d\r\n",SpeedD);

	 printf("target:%d",target_SpeedA);
	 printf("target:%d",target_SpeedB);
	 printf("target:%d",target_SpeedC);
	 printf("target:%d\r\n",target_SpeedD);
	 
	 
     printf("nowA:%f(rad)\r\n",Motor_SpeedA);
	 printf("nowB:%f(rad)\r\n",Motor_SpeedB);
	 printf("nowC:%f(rad)\r\n",Motor_SpeedC);
	 printf("nowD:%f(rad)\r\n",Motor_SpeedD);


}




