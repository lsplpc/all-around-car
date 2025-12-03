#include "stm32f4xx.h"                  // Device header


void PWM_Init(void)
{   GPIO_InitTypeDef GPIO_InitStructure;//初始化GPIO端口参数
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
//定时中断初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//配置时钟

	//复用推挽输出(定时器控制GPIO) 输出有八种模式可选
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15 ;   //选择要初始化的端口 可以用或符号（ | ）选择多个
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz ; //初始化参数
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIO端口
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);//绑定
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);//绑定
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);//绑定
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM12);//绑定
	
	//复用推挽输出(定时器控制GPIO) 输出有八种模式可选
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7;   //选择要初始化的端口 可以用或符号（ | ）选择多个
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz ; //初始化参数
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO端口
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);//绑定
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);//绑定
	
	
	
    TIM_InternalClockConfig(TIM3);//选择内部时钟 选择tim3计时器
  
	Tim_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//配置滤波采样频率
	Tim_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//配置计数方式 这里选择的是向上计数
	Tim_TimeBaseInitStructure.TIM_Period = 99;//周期 arr自动重装器的值 计数器的最大值 达到一次最大值后发出信号
	Tim_TimeBaseInitStructure.TIM_Prescaler = 12799;//PSC预分频器的值 计数的频率 值越大达到最大值的速度越快 有公式的 自己算
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器 高级计时器才用得到
    TIM_TimeBaseInit(TIM3,&Tim_TimeBaseInitStructure);//时基单元配置ok
	
	TIM_InternalClockConfig(TIM12);//选择内部时钟 选择tim12计时器
  
	Tim_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//配置滤波采样频率
	Tim_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//配置计数方式 这里选择的是向上计数
	Tim_TimeBaseInitStructure.TIM_Period = 99;//周期 arr自动重装器的值 计数器的最大值 达到一次最大值后发出信号
	Tim_TimeBaseInitStructure.TIM_Prescaler = 12799;//PSC预分频器的值 计数的频率 值越大达到最大值的速度越快 有公式的 自己算
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器 高级计时器才用得到
    TIM_TimeBaseInit(TIM12,&Tim_TimeBaseInitStructure);//时基单元配置ok
	
	
	
	
	TIM_OCStructInit(&TIM_OCInitStructure);//因为如果不给所有参数赋值可能导致程序出错，所以这里先初始化
	                                       //一次这个结构体 这个函数的作用就是直接初始化这个结构体
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1 ;//设置输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//设置输出比较的极性（这里配置高极性）
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable ;//设置输出使能
	 
	 TIM_OCInitStructure.TIM_Pulse = 0;//设置CCR (这个结构体又很多参数，这里只列了要用的)
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);  //使用tim3通道1输出
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);  //使用tim3通道2输出
	 
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);  //使用tim3通道3输出
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);  //使用tim3通道4输出
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM12,&TIM_OCInitStructure);  //使用tim12通道1输出
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM12,&TIM_OCInitStructure);  //使用tim12通道2输出
	
	
	// 6. 开启预装载功能（重要！）
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM12, ENABLE);
	
    // 7. 使能PWM输出（关键！）
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM12, ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);//开启定时器
	TIM_Cmd(TIM12,ENABLE);
	
	
}

void PWM_SetCompare1(uint16_t Compare)//
{
  TIM_SetCompare1(TIM3,Compare);//在运行过程中更改tim3通道1的CCR


}

void PWM_SetCompare2(uint16_t Compare)
{
  TIM_SetCompare2(TIM3,Compare);//在运行过程中更改tim3通道2的CCR


}



void PWM_SetCompare3(uint16_t Compare)
{
  TIM_SetCompare3(TIM3,Compare);//在运行过程中更改tim3通道3的CCR


}

void PWM_SetCompare4(uint16_t Compare)
{
  TIM_SetCompare4(TIM3,Compare);//在运行过程中更改tim3通道4的CCR


}

void PWM_SetCompare5(uint16_t Compare)
{
  TIM_SetCompare1(TIM12,Compare);//在运行过程中更改tim12通道1的CCR


}

void PWM_SetCompare6(uint16_t Compare)
{
  TIM_SetCompare2(TIM12,Compare);//在运行过程中更改tim12通道2的CCR


}
