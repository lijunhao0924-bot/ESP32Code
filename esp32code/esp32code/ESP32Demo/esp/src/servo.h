#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>

// 可修改：舵机控制引脚（根据你的硬件调整）
#ifndef SERVO_PIN
#define SERVO_PIN 18
#endif

// 舵机命令（通过任务通知发送）
typedef enum {
  SERVO_CMD_STOP = 0,
  SERVO_CMD_CW = 1,
  SERVO_CMD_CCW = 2
} ServoCommand;

// 初始化舵机硬件
void initServo(uint8_t pin);

// RTOS 任务：等待通知并执行舵机动作
void servoTask(void *param);

// 直接设置舵机为停止/顺/逆
void applyServoCommand(ServoCommand cmd);

#endif
