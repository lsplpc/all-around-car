#ifndef __ENCODER_H
#define __ENCODER_H
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
void Encoder_Init_TIM8(void);
void Encoder_Init_TIM1(void);
void Encoder_Init_TIM5(void);
void Encoder_Init_TIM9(void);
int Read_EncoderD(void);
int Read_EncoderC(void);
int Read_EncoderB(void);
int Read_EncoderA(void);
int Read_EncoderE(void);
int Read_EncoderF(void);
void TIM1_BRK_TIM9_IRQHandler(void);
#endif
