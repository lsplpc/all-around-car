#ifndef CARCONTROL_H
#define CARCONTROL_H

#include "stm32f4xx.h"
#include <stdint.h>
#include <string.h>



void Parse_KeyCmd(void);
void CarControl_Init(void);
extern int16_t target_SpeedA;
extern int16_t target_SpeedB;
extern int16_t target_SpeedC;
extern int16_t target_SpeedD;
#endif /* CARCONTROL_H */
