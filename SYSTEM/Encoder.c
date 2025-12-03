#include "stm32f4xx.h"                  // Device header

static int32_t Encoder_Count_TIM9 = 0;
static uint8_t Encoder_LastState_TIM9 = 0;

void Encoder_Init_TIM2(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;
    // 1. 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   // 使能TIM2时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
    // 2. 配置GPIO（PA0、PA1为定时器复用输入）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);//绑定

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);//绑定
	

    // 3. 配置TIM2时基
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 65535;            // 最大计数范围（16位）
    TIM_TimeBaseStructure.TIM_Prescaler = 0;             // 不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 4. 配置编码器模式（正交解码）
    // Encoder.c 中 TIM_EncoderInterfaceConfig 配置
TIM_EncoderInterfaceConfig(TIM2,  
                          TIM_EncoderMode_TI12,       // 同时使用TI1和TI2
                          TIM_ICPolarity_BothEdge,    // 原为 Rising，改为双边沿检测
                          TIM_ICPolarity_BothEdge);   // 双边沿检测
						  			  

    // 5. 配置输入捕获滤波（可选，滤除噪声）
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6; // 滤波值（0~15，值越大滤波越强）
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
	

    // 6. 启动定时器
    TIM_Cmd(TIM2, ENABLE);
    TIM2->CNT = 0; 
	
}

void Encoder_Init_TIM4(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   // 使能TIM4时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // 使能GPIOD时钟  PB6 7   
	
    // 2. 配置GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);//绑定
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	
    // 3. 配置TIM4时基
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 65535;            // 最大计数范围（16位）
    TIM_TimeBaseStructure.TIM_Prescaler = 0;             // 不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    // 4. 配置编码器模式（正交解码）
    // Encoder.c 中 TIM_EncoderInterfaceConfig 配置
TIM_EncoderInterfaceConfig(TIM4,  
                          TIM_EncoderMode_TI12,       // 同时使用TI1和TI2
                          TIM_ICPolarity_BothEdge,    // 原为 Rising，改为双边沿检测
                          TIM_ICPolarity_BothEdge);   // 双边沿检测
						  			  

    // 5. 配置输入捕获滤波（可选，滤除噪声）
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6; // 滤波值（0~15，值越大滤波越强）
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
	

    // 6. 启动定时器
    TIM_Cmd(TIM4, ENABLE);
    TIM4->CNT = 0; 
	
}

void Encoder_Init_TIM8(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   // 使能TIM8时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // 使能GPIOC时钟  PC6 7   
	
    // 2. 配置GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);//绑定
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	
    // 3. 配置TIM8时基
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 65535;            // 最大计数范围（16位）
    TIM_TimeBaseStructure.TIM_Prescaler = 0;             // 不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    // 4. 配置编码器模式（正交解码）
    // Encoder.c 中 TIM_EncoderInterfaceConfig 配置
TIM_EncoderInterfaceConfig(TIM8,  
                          TIM_EncoderMode_TI12,       // 同时使用TI1和TI2
                          TIM_ICPolarity_BothEdge,    // 原为 Rising，改为双边沿检测
                          TIM_ICPolarity_BothEdge);   // 双边沿检测
						  			  

    // 5. 配置输入捕获滤波（可选，滤除噪声）
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6; // 滤波值（0~15，值越大滤波越强）
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
	

    // 6. 启动定时器
    TIM_Cmd(TIM8, ENABLE);
    TIM8->CNT = 0; 
	
}

void Encoder_Init_TIM1(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   // 使能TIM1时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能GPIOA时钟  PA8 9   
	
    // 2. 配置GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);//绑定
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	
    // 3. 配置TIM1时基
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 65535;            // 最大计数范围（16位）
    TIM_TimeBaseStructure.TIM_Prescaler = 0;             // 不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    // 4. 配置编码器模式（正交解码）
    // Encoder.c 中 TIM_EncoderInterfaceConfig 配置
TIM_EncoderInterfaceConfig(TIM1,  
                          TIM_EncoderMode_TI12,       // 同时使用TI1和TI2
                          TIM_ICPolarity_BothEdge,    // 原为 Rising，改为双边沿检测
                          TIM_ICPolarity_BothEdge);   // 双边沿检测
						  			  

    // 5. 配置输入捕获滤波（可选，滤除噪声）
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6; // 滤波值（0~15，值越大滤波越强）
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
	

    // 6. 启动定时器
    TIM_Cmd(TIM1, ENABLE);
    TIM1->CNT = 0; 
	
}

void Encoder_Init_TIM5(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   // 使能TIM5时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能GPIOA时钟  PA0 1   
	
    // 2. 配置GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);//绑定
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
    // 3. 配置TIM1时基
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 65535;            // 最大计数范围（16位）
    TIM_TimeBaseStructure.TIM_Prescaler = 0;             // 不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    // 4. 配置编码器模式（正交解码）
    // Encoder.c 中 TIM_EncoderInterfaceConfig 配置
TIM_EncoderInterfaceConfig(TIM5,  
                          TIM_EncoderMode_TI12,       // 同时使用TI1和TI2
                          TIM_ICPolarity_BothEdge,    // 原为 Rising，改为双边沿检测
                          TIM_ICPolarity_BothEdge);   // 双边沿检测
						  			  

    // 5. 配置输入捕获滤波（可选，滤除噪声）
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6; // 滤波值（0~15，值越大滤波越强）
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
	

    // 6. 启动定时器
    TIM_Cmd(TIM5, ENABLE);
    TIM5->CNT = 0; 
	
}

void Encoder_Init_TIM9(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能时钟（TIM9=APB2，GPIOA=AHB1）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
    // 2. 配置 PA2（TIM9_CH1）、PA3（TIM9_CH2）为复用输入（输入捕获模式）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          // 复用功能
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          // 上拉输入（必须改，防浮空）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 3. 绑定复用 AF3（TIM9 正确 AF 编号）
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);
	
    // 4. 配置 TIM9 时基（1MHz 计数时钟，响应编码器信号）
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;          // 最大周期，不溢出
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;       // 84MHz（APB2时钟）/84 = 1MHz
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

    // 5. 配置 CH1（PA2）输入捕获（上升沿+下降沿触发，检测所有电平变化）
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // 先设上升沿
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICFilter = 6; // 滤波，防噪声
    TIM_ICInit(TIM9, &TIM_ICInitStructure);
    
    // 6. 配置 CH2（PA3）输入捕获（同上）
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM9, &TIM_ICInitStructure);
    
    // 7. 开启 CH1/CH2 输入捕获中断（关键：检测电平变化）
    TIM_ITConfig(TIM9, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);
    
    // 8. 配置 TIM9 中断优先级（确保快速响应）
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn; // TIM9 中断通道！
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // 高子优先级
    NVIC_Init(&NVIC_InitStructure);
    
    // 9. 启动 TIM9
    TIM_Cmd(TIM9, ENABLE);
    
    // 初始化：读取 PA2/PA3 初始电平状态
    Encoder_LastState_TIM9 = ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) << 1) | 
                              GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
}

int Read_EncoderA(void)
{
    int count = (short)TIM2->CNT; // 读取TIM2计数器值（强转为short区分正负）
    TIM2->CNT = 0;                // 读取后清零，下次读取增量
    return count;
}

int Read_EncoderB(void)
{
    int count = (short)TIM4->CNT; // 读取TIM4计数器值（强转为short区分正负）
    TIM4->CNT = 0;                // 读取后清零，下次读取增量
    return count;
}

int Read_EncoderC(void)
{
    int count = (short)TIM8->CNT; // 读取TIM8计数器值（强转为short区分正负）
    TIM8->CNT = 0;                // 读取后清零，下次读取增量
    return count;
}

int Read_EncoderD(void)
{
    int count = (short)TIM1->CNT; // 读取TIM1计数器值（强转为short区分正负）
    TIM1->CNT = 0;                // 读取后清零，下次读取增量
    return count;
}

int Read_EncoderE(void)
{
    int count = (short)TIM5->CNT; // 读取TIM5计数器值（强转为short区分正负）
    TIM5->CNT = 0;                // 读取后清零，下次读取增量
    return count;
}

int Read_EncoderF(void)
{
    // 读取增量计数并清零（和其他编码器用法一致）
    int32_t temp = Encoder_Count_TIM9;
    Encoder_Count_TIM9 = 0;
    return (int)temp;
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    uint8_t current_state = 0;
    
    // 检测 CH1 中断（PA2 电平变化）
    if (TIM_GetITStatus(TIM9, TIM_IT_CC1) != RESET)
    {
        TIM_ClearITPendingBit(TIM9, TIM_IT_CC1);
        current_state = ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) << 1) | 
                         GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
    }
    
    // 检测 CH2 中断（PA3 电平变化）
    if (TIM_GetITStatus(TIM9, TIM_IT_CC2) != RESET)
    {
        TIM_ClearITPendingBit(TIM9, TIM_IT_CC2);
        current_state = ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) << 1) | 
                         GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
    }
    
    // 软件解码：根据前后状态判断正反转
    if (current_state != Encoder_LastState_TIM9)
    {
        // 正转：00→01→11→10→00（计数+1）
        if (((Encoder_LastState_TIM9 & 0x01) == 0) && ((current_state & 0x02) != 0))
        {
            Encoder_Count_TIM9++;
        }
        // 反转：00→10→11→01→00（计数-1）
        else if (((Encoder_LastState_TIM9 & 0x02) == 0) && ((current_state & 0x01) != 0))
        {
            Encoder_Count_TIM9--;
        }
        Encoder_LastState_TIM9 = current_state; // 更新上一次状态
    }
}
