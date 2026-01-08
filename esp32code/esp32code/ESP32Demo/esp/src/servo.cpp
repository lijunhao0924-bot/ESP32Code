#include "servo.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>

// LEDC 通道、频率和分辨率
static const int LEDC_CHANNEL = 0;
static const int SERVO_FREQ = 50; // 50Hz 常见舵机频率
static const int SERVO_RES = 10;  // 分辨率 10-bit -> 0..1023

// 将微秒脉宽转换为 ledc 写入值
static int usToDuty(uint32_t us) {
  // 周期 20ms = 20000us
  return (int)((us * (1 << SERVO_RES)) / 20000UL);
}

void initServo(uint8_t pin) {
  ledcSetup(LEDC_CHANNEL, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(pin, LEDC_CHANNEL);
  // 设为停止脉宽（约1500us）
  ledcWrite(LEDC_CHANNEL, usToDuty(1500));
}

void applyServoCommand(ServoCommand cmd) {
  switch (cmd) {
    case SERVO_CMD_STOP:
      // 停止（中立）
      ledcWrite(LEDC_CHANNEL, usToDuty(1500));
      break;
    case SERVO_CMD_CW:
      // 顺时针：较短脉宽（例如1300us），速度可通过更改该值调节
      ledcWrite(LEDC_CHANNEL, usToDuty(1300));
      break;
    case SERVO_CMD_CCW:
      // 逆时针：较长脉宽（例如1700us）
      ledcWrite(LEDC_CHANNEL, usToDuty(1700));
      break;
    default:
      ledcWrite(LEDC_CHANNEL, usToDuty(1500));
      break;
  }
}

void servoTask(void *param) {
  uint32_t notifValue = 0;
  while (true) {
    // 等待任务通知，并接收通知值作为命令
    if (xTaskNotifyWait(0x00, 0xffffffff, &notifValue, portMAX_DELAY) == pdTRUE) {
      uint32_t cmd = notifValue & 0xff;
      if (cmd == SERVO_CMD_CW) {
        applyServoCommand(SERVO_CMD_CW);
      } else if (cmd == SERVO_CMD_CCW) {
        applyServoCommand(SERVO_CMD_CCW);
      } else {
        applyServoCommand(SERVO_CMD_STOP);
      }
    }
  }
}
