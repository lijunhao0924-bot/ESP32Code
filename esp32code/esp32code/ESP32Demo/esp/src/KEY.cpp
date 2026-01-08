#include "key.h"
#include "global_data.h"
#include "servo.h"

// 定义全局页面变量
DisplayPage currentPage = PAGE_ENV;

// 按键防抖参数
#define DEBOUNCE_DELAY 20 // 防抖延时20ms
#define LONG_PRESS_MS 700 // 长按判定
unsigned long lastKeyPressTime = 0;

// 初始化按键（上拉输入）
void setupKeys() {
  pinMode(KEY1_PIN, INPUT_PULLUP);
  pinMode(KEY2_PIN, INPUT_PULLUP);
  pinMode(KEY3_PIN, INPUT_PULLUP);
  Serial.println("按键模块初始化完成");
}

// 读取按键（防抖与长按处理）
void readKeys() {
  // 读取三路按键，长按触发舵机命令，短按保留原有翻页功能
  // 按键1（KEY1_PIN）：短按切环境页，长按 -> 顺时针
  if (digitalRead(KEY1_PIN) == LOW) {
    if (millis() - lastKeyPressTime > DEBOUNCE_DELAY) {
      unsigned long t0 = millis();
      // 等待按键释放
      while (digitalRead(KEY1_PIN) == LOW) {
        vTaskDelay(pdMS_TO_TICKS(10));
      }
      unsigned long duration = millis() - t0;
      lastKeyPressTime = millis();
      if (duration >= LONG_PRESS_MS) {
        Serial.println("按键1长按 → 舵机顺时针（CW）");
        if (servoTaskHandle) {
          xTaskNotify(servoTaskHandle, (uint32_t)SERVO_CMD_CW, eSetValueWithOverwrite);
        }
      } else {
        currentPage = PAGE_ENV;
        Serial.println("按键1短按 → 切换到环境数据页");
      }
    }
  }
  // 按键2（KEY2_PIN）：短按切WiFi页，长按 -> 停止舵机
  else if (digitalRead(KEY2_PIN) == LOW) {
    if (millis() - lastKeyPressTime > DEBOUNCE_DELAY) {
      unsigned long t0 = millis();
      while (digitalRead(KEY2_PIN) == LOW) {
        vTaskDelay(pdMS_TO_TICKS(10));
      }
      unsigned long duration = millis() - t0;
      lastKeyPressTime = millis();
      if (duration >= LONG_PRESS_MS) {
        Serial.println("按键2长按 → 舵机停止（STOP）");
        if (servoTaskHandle) {
          xTaskNotify(servoTaskHandle, (uint32_t)SERVO_CMD_STOP, eSetValueWithOverwrite);
        }
      } else {
        currentPage = PAGE_WIFI;
        Serial.println("按键2短按 → 切换到WiFi信息页");
      }
    }
  }
  // 按键3（KEY3_PIN）：短按切调试页，长按 -> 逆时针
  else if (digitalRead(KEY3_PIN) == LOW) {
    if (millis() - lastKeyPressTime > DEBOUNCE_DELAY) {
      unsigned long t0 = millis();
      while (digitalRead(KEY3_PIN) == LOW) {
        vTaskDelay(pdMS_TO_TICKS(10));
      }
      unsigned long duration = millis() - t0;
      lastKeyPressTime = millis();
      if (duration >= LONG_PRESS_MS) {
        Serial.println("按键3长按 → 舵机逆时针（CCW）");
        if (servoTaskHandle) {
          xTaskNotify(servoTaskHandle, (uint32_t)SERVO_CMD_CCW, eSetValueWithOverwrite);
        }
      } else {
        currentPage = PAGE_DEBUG;
        Serial.println("按键3短按 → 切换到调试信息页");
      }
    }
  }
}