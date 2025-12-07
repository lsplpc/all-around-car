#include "stm32f4xx.h"                  // Device header
#include "PID.h"
#include "Serial.h"
void read_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure={0};
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_RESET);

}

float xunji (unsigned char Digtal)
{ 
  int A1=0,A2=0,A3=0,A4=0,A5=0,A6=0,A7=0,A8=0;
  float z = 0 ,xun=0 ,last_xun,cha=0;
  PID readpid;
  Speed_PID_Init(&readpid, 5 , 0.1 , 0.1 , 100);
  
	if( 0 <((Digtal>>0)&0x01)) {A1=0;}else{A1=1;z++;}//C 语言中，<（关系运算符）的优先级 高于 &（按位与运算符
    if( 0 <((Digtal>>1)&0x01)) {A2=0;}else{A2=1;z++;}
    if( 0 <((Digtal>>2)&0x01)) {A3=0;}else{A3=1;z++;}
    if( 0 <((Digtal>>3)&0x01)) {A4=0;}else{A4=1;z++;}
    if( 0 <((Digtal>>4)&0x01)) {A5=0;}else{A5=1;z++;}
    if( 0 <((Digtal>>5)&0x01)) {A6=0;}else{A6=1;z++;}
    if( 0 <((Digtal>>6)&0x01)) {A7=0;}else{A7=1;z++;}
    if( 0 <((Digtal>>7)&0x01)) {A8=0;}else{A8=1;z++;}
	
	if (z==0)z=1;
	
	xun =(float)(A1*1 + A2*2 + A3*3 + A4*4 + A5*5 + A6*6 + A7*7 + A8*8)/z;
	
	if(xun!=0){last_xun = xun;}
	else if(xun==0){xun = last_xun;}
	
//	printf("xun:%.1f)\r\n",xun);
//	printf("-%d-%d-%d-%d-%d-%d-%d-%d-\r\n",A1,A2,A3,A4,A5,A6,A7,A8);
	
    cha = PID_Incremental_Calc(&readpid,4.5,xun); //循迹 

	printf("cha:%.1f\r\n",cha);
	
	return cha;
}












