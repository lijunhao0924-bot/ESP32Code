#include "key.h"

// 定义全局页面变量
DisplayPage currentPage = PAGE_ENV;

// 按键防抖参数
#define DEBOUNCE_DELAY 20 // 防抖延时20ms
unsigned long lastKeyPressTime = 0;

// 初始化按键（上拉输入）
void setupKeys() {
  pinMode(KEY1_PIN, INPUT_PULLUP);
  pinMode(KEY2_PIN, INPUT_PULLUP);
  pinMode(KEY3_PIN, INPUT_PULLUP);
  Serial.println("按键模块初始化完成");
}

// 读取按键（防抖处理）
void readKeys() {
  // 防抖：短时间内只处理一次按键


  // 按键1（15号引脚）：切换到环境数据页（低电平表示按下，上拉输入）
  if (digitalRead(KEY1_PIN) == LOW) {
     if (millis() - lastKeyPressTime > DEBOUNCE_DELAY) 
     {
        currentPage = PAGE_ENV;
        lastKeyPressTime = millis();
        Serial.println("按键1按下 → 切换到环境数据页");
        while(digitalRead(KEY1_PIN) == LOW)
        {
         
        }
     }
   
  }
  // 按键2（16号引脚）：切换到WiFi信息页
  else if (digitalRead(KEY2_PIN) == LOW) {
    if (millis() - lastKeyPressTime > DEBOUNCE_DELAY)
    {
            currentPage = PAGE_WIFI;
            lastKeyPressTime = millis();
            Serial.println("按键2按下 → 切换到WiFi信息页");
    }
     while(digitalRead(KEY2_PIN) == LOW)
        {
         
        }

  }
  // 按键3（17号引脚）：切换到调试信息页
  else if (digitalRead(KEY3_PIN) == LOW) {
    if (millis() - lastKeyPressTime > DEBOUNCE_DELAY)
    {
        currentPage = PAGE_DEBUG;
        lastKeyPressTime = millis();
        Serial.println("按键3按下 → 切换到调试信息页");
    }
    while(digitalRead(KEY3_PIN) == LOW)
        {
         
        }
  }

}