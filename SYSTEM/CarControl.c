#include "CarControl.h"
#include "delay.h"
#include <string.h>
#include "Serial.h"
#include "PID.h"
#include "Encoder.h"
#include "Motor.h"


int16_t target_SpeedA = 0;
int16_t target_SpeedB = 0;
int16_t target_SpeedC = 0;
int16_t target_SpeedD = 0;

void CarControl_Init(void) {
    // 无独立初始化逻辑，依赖main中其他模块的初始化
}

void Parse_KeyCmd(void) {
    if (Serial_GetRxFlag()) {
        char cmd[32] = {0};
        strncpy(cmd, (char*)Serial_GetRxBuf(), 32);
        Serial_ClearRxBuf();
     
 
        if (strstr(cmd, "1") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')){
            target_SpeedA=100;  target_SpeedB=100 ; target_SpeedC=100  ;target_SpeedD=100 ;
            Serial_SendString("执行：前进（麦克纳姆轮全向）\r\n");
        } else if (strstr(cmd, "2") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
           target_SpeedA=-100;  target_SpeedB=-100 ; target_SpeedC=-100  ;target_SpeedD=-100 ;
            Serial_SendString("执行：后退（麦克纳姆轮全向）\r\n");
        } else if (strstr(cmd, "3") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=-100;  target_SpeedB=100 ; target_SpeedC=-100  ;target_SpeedD=100 ;
            Serial_SendString("执行：左移（麦克纳姆轮横向）\r\n");
        } else if (strstr(cmd, "4") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=100;  target_SpeedB=-100 ; target_SpeedC=100  ;target_SpeedD=-100 ;
            Serial_SendString("执行：右移（麦克纳姆轮横向）\r\n");
        } else if (strstr(cmd, "5") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=100;  target_SpeedB=100 ; target_SpeedC=-100  ;target_SpeedD=-100 ;
            Serial_SendString("执行：原地左转（麦克纳姆轮旋转）\r\n");
        } else if (strstr(cmd, "6") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=-100;  target_SpeedB=-100 ; target_SpeedC=100  ;target_SpeedD=100 ;
            Serial_SendString("执行：原地右转（麦克纳姆轮旋转）\r\n");
        } else if (strstr(cmd, "7") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=0;  target_SpeedB=100 ; target_SpeedC=0  ;target_SpeedD=100 ;
            Serial_SendString("执行：左前斜移（麦克纳姆轮斜向）\r\n");
        } else if (strstr(cmd, "8") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=100;  target_SpeedB=0 ; target_SpeedC=100  ;target_SpeedD=0 ;
            Serial_SendString("执行：右前斜移（麦克纳姆轮斜向）\r\n");
        } else if (strstr(cmd, "9") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=-100;  target_SpeedB=0 ; target_SpeedC=-100  ;target_SpeedD=0 ;
            Serial_SendString("执行：左后斜移（麦克纳姆轮斜向）\r\n");
        } else if (strstr(cmd, "A") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
            target_SpeedA=0;  target_SpeedB=-100 ; target_SpeedC=0  ;target_SpeedD=-100 ;
            Serial_SendString("执行：右后斜移（麦克纳姆轮斜向）\r\n");
        }else if (strstr(cmd, "0") != NULL && (cmd[1] == '\r' || cmd[1] == '\n' || cmd[1] == '\0')) {
             target_SpeedA=0;  target_SpeedB=0 ; target_SpeedC=0  ;target_SpeedD=0 ;
            Serial_SendString("执行：停止\r\n");
        } else {
            Serial_SendString("指令无效！请输入1-10（麦克纳姆轮全向控制）\r\n");
            Serial_SendString("1=前进 2=后退 3=左移 4=右移 5=原地左转 6=原地右转 7=左前 8=右前 9=左后 10=停止\r\n");
        }
    }
}

