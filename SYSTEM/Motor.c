#include "stm32f4xx.h"                  // Device header

#include "PWM.h"


void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_IntstStrure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_IntstStrure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntstStrure.GPIO_OType = GPIO_OType_PP; 
	GPIO_IntstStrure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_IntstStrure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_IntstStrure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_IntstStrure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_IntstStrure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntstStrure.GPIO_OType = GPIO_OType_PP; 
	GPIO_IntstStrure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_IntstStrure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_IntstStrure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_IntstStrure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_IntstStrure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntstStrure.GPIO_OType = GPIO_OType_PP; 
	GPIO_IntstStrure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_IntstStrure.GPIO_Pin =GPIO_Pin_12 |GPIO_Pin_13;
	GPIO_IntstStrure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_IntstStrure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_IntstStrure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntstStrure.GPIO_OType = GPIO_OType_PP; 
	GPIO_IntstStrure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_IntstStrure.GPIO_Pin =GPIO_Pin_0 |GPIO_Pin_1;
	GPIO_IntstStrure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_IntstStrure);
	
	
	
	
	
	
 PWM_Init();

	
}

void Motor_SetSpeedA(int8_t Speed)
{
  if (Speed>=0)
  {
   GPIO_SetBits(GPIOC,GPIO_Pin_0);
   GPIO_ResetBits(GPIOC,GPIO_Pin_1);
   PWM_SetCompare3(Speed);
  }
  else
  {
   GPIO_SetBits(GPIOC,GPIO_Pin_1);
   GPIO_ResetBits(GPIOC,GPIO_Pin_0);
   PWM_SetCompare3(-Speed);
  
  }

}
void Motor_SetSpeedB(int8_t Speed)
{
  if (Speed>=0)
  {
   GPIO_SetBits(GPIOE,GPIO_Pin_1);
   GPIO_ResetBits(GPIOE,GPIO_Pin_0);
   PWM_SetCompare4(Speed);
  }
  else
  {
   GPIO_SetBits(GPIOE,GPIO_Pin_0);
   GPIO_ResetBits(GPIOE,GPIO_Pin_1);
   PWM_SetCompare4(-Speed);
  
  }

}


void Motor_SetSpeedC(int8_t Speed)
{
  if (Speed>=0)
  {
   GPIO_SetBits(GPIOE,GPIO_Pin_2);
   GPIO_ResetBits(GPIOE,GPIO_Pin_3);
   PWM_SetCompare1(Speed);
  }
  else
  {
   GPIO_SetBits(GPIOE,GPIO_Pin_3);
   GPIO_ResetBits(GPIOE,GPIO_Pin_2);
   PWM_SetCompare1(-Speed);
  
  }

}

void Motor_SetSpeedD(int8_t Speed)
{
  if (Speed>=0)
  {
   GPIO_SetBits(GPIOB,GPIO_Pin_12);
   GPIO_ResetBits(GPIOB,GPIO_Pin_13);
   PWM_SetCompare2(Speed);
  }
  else
  {
   GPIO_SetBits(GPIOB,GPIO_Pin_13);
   GPIO_ResetBits(GPIOB,GPIO_Pin_12);
   PWM_SetCompare2(-Speed);
  
  }

}

void Motor_SetSpeedE(int8_t Speed)//两轮共用不可行
{
  if (Speed>=0)
  {
   GPIO_SetBits(GPIOC,GPIO_Pin_2);
   GPIO_ResetBits(GPIOC,GPIO_Pin_3);
   PWM_SetCompare5(Speed);
  }
  else
  {
   GPIO_SetBits(GPIOC,GPIO_Pin_3);
   GPIO_ResetBits(GPIOC,GPIO_Pin_2);
   PWM_SetCompare5(-Speed);
  
  }

}

void Motor_SetSpeedF(int8_t Speed)
{
  if (Speed>=0)
  {
   GPIO_SetBits(GPIOD,GPIO_Pin_0);
   GPIO_ResetBits(GPIOD,GPIO_Pin_1);
   PWM_SetCompare6(Speed);
  }
 else
	 {
  GPIO_SetBits(GPIOD,GPIO_Pin_0);
  GPIO_ResetBits(GPIOD,GPIO_Pin_1);
  PWM_SetCompare6(-Speed);
 
 }

}
