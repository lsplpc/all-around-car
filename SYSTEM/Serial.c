#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "Serial.h"
#include <string.h>
#include "Serial.h"


uint8_t Serial_TxPacket[4];//发包
uint8_t Serial_RxPacket[4];//接收缓存数组


volatile uint8_t Serial_RxFlag = 0;  // 唯一的定义点
volatile uint8_t Serial_RxBuf[SERIAL_RX_BUF_LEN] = {0};
volatile uint8_t Serial_RxIndex = 0;

void Serial_Init(void)
{    
	GPIO_InitTypeDef GPIO_IntstStrure;//初始化GPIO
	USART_InitTypeDef USART_InitStruture;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	
    GPIO_IntstStrure.GPIO_Mode =GPIO_Mode_AF;
	GPIO_IntstStrure.GPIO_OType = GPIO_OType_PP;
	GPIO_IntstStrure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_IntstStrure.GPIO_Pin =GPIO_Pin_8 |GPIO_Pin_9;
	GPIO_IntstStrure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_IntstStrure);
	
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);  
	
	
	USART_InitStruture.USART_BaudRate = 115200;//波特率
	USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//选择输入输出
	USART_InitStruture.USART_Parity = USART_Parity_No;//是否需要校验
	USART_InitStruture.USART_StopBits = USART_StopBits_1;//停止位
	USART_InitStruture.USART_WordLength = USART_WordLength_8b;//八位字长
	USART_Init(USART3,&USART_InitStruture);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//RX专用中断 开启RXNE标志位到NVIC的输出
	                                            //随后下面的函数检测置一开启下面的中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART3,ENABLE);
}

void Serial_SendByte(uint8_t Byte)//发送字符
{
  USART_SendData(USART3,Byte);
  while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//判断发送空寄存器到标志位
}                                                               
void Serial_SendArray(uint8_t *Array,uint16_t Length)//发送数组
{
  uint16_t i;
  for(i=0;i<Length;i++)
	{
	  Serial_SendByte(Array[i]);
	
	}

}

void Serial_SendString(char *String)//制服串
{
    uint8_t i;
	for(i=0;String[i]!='\0';i++)//字符串有标志位
	{
	 Serial_SendByte(String[i]);
	
	}
  
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
 uint32_t Result =1;
 while(Y--)
 {
   Result *= X;
 }
  return Result;
}


void Serial_SendNumber(uint32_t Number,uint8_t Length)//发数字
{
  uint8_t i;
  for(i=0;i<Length;i++)
  {
   Serial_SendByte(Number/Serial_Pow(10,Length-i-1) % 10 + 0x30);
  }

}
	int fputc(int ch,FILE *f)//因为printf默认输出到屏幕但是这个没有屏幕所以现在重定义他输出到串口1
    {
	  Serial_SendByte(ch);
	  return ch;
	}
	
void Serial_Printf(char *format,...)//可变参数printf
{
char String[100];
  va_list arg;
  __va_start(arg,format);
  vsprintf(String,format,arg);	
  __va_end(arg);
  Serial_SendString(String);
}

void Serial_SendPacket(void)//打包包 薇尔莉特
{
 Serial_SendByte(0xFF);//包头
Serial_SendArray(Serial_TxPacket,4);
Serial_SendByte(0xFE);//包尾
}



//new
uint8_t* Serial_GetRxBuf(void) {
    return (uint8_t*)Serial_RxBuf;
}

void Serial_ClearRxBuf(void) {
    memset((char*)Serial_RxBuf, 0, SERIAL_RX_BUF_LEN);
    Serial_RxFlag = 0;
    Serial_RxIndex = 0;
}



//new
uint8_t Serial_GetRxFlag(void)//与接收函数内的Serial_RxFlag联动 判断是否接收完毕
{
  if(Serial_RxFlag==1)
  {
   Serial_RxFlag=0;
   return 1;
  }
  return 0;
}


void USART3_IRQHandler(void)
{
    uint8_t RxData;
    // 检查是否接收到数据
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        RxData = USART_ReceiveData(USART3); // 读取接收到的数据
        
        // 关键逻辑：将接收到的数据存入缓冲区
        if (Serial_RxIndex < SERIAL_RX_BUF_LEN - 1) // 留出一个字节给字符串结束符 '\0'
        {
            // 如果收到回车符 '\r'，说明指令结束
            if (RxData == '\r') 
            {
                Serial_RxBuf[Serial_RxIndex] = '\0'; // 添加字符串结束符
                Serial_RxFlag = 1; // 置位接收完成标志
            }
            else
            {
                Serial_RxBuf[Serial_RxIndex++] = RxData;
            }
        }
        else // 如果缓冲区满了，也强制置位标志，防止溢出
        {
            Serial_RxBuf[Serial_RxIndex] = '\0';
            Serial_RxFlag = 1;
        }

        USART_ClearITPendingBit(USART3, USART_IT_RXNE); // 清除中断标志位
    }
}
