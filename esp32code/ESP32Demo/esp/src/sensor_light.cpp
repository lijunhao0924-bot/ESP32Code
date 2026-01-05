#include <Arduino.h>
#include "sensor_light.h"
bool lightStatus = true;
  int count = 0;
// ========== 初始化函数（正确） ==========
void SetupLDR() {
  pinMode(SerPIN, INPUT);    // 光敏DO引脚=输入
  pinMode(lightPIN, OUTPUT); // 小灯引脚=输出
  digitalWrite(lightPIN, LIGHT_OFF); // 初始灭灯
  Serial.begin(115200); // 初始化串口（你之前漏了！）
  Serial.println("光敏模块初始化完成");
}

// ========== 防抖读取+小灯控制（逻辑完全修复） ==========
void readDOWithDebounce() {
  // 1. 防抖：统计「无遮挡=HIGH」的次数
  int highCount = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(SerPIN) == HIGH) { // 无遮挡=高电平（和注释一致）
      highCount++;
    }
    delay(10); // 防抖延时
  }

  // 2. 判断光照状态：highCount≥2 → 无遮挡（光照充足）
  bool isLightEnough = (highCount >= 2);

  // 3. 正确逻辑：遮挡→亮灯，无遮挡→灭灯
  if (isLightEnough) { // 光照不足（遮挡）→ 小灯亮
    digitalWrite(lightPIN, LIGHT_ON); 
    lightStatus = false;
    count++;
    Serial.println("遮挡传感器 → 小灯亮");
  } else { // 光照充足（无遮挡）→ 小灯灭
    lightStatus = true;
    digitalWrite(lightPIN, LIGHT_OFF);
    Serial.println("无遮挡 → 小灯灭");
   

  }

  // 调试用：打印原始电平，方便排查
  Serial.printf("调试：SerPIN原始电平=%d，高电平次数=%d\n", digitalRead(SerPIN),count);
}

