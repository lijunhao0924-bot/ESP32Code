#include <Arduino.h>
#include "sensor_light.h"
bool lightStatus = true;
int count = 0;
//初始化函数
void SetupLDR() {
  pinMode(SerPIN, INPUT);    // 光敏DO引脚=输入
  pinMode(lightPIN, OUTPUT); // 小灯引脚=输出
  digitalWrite(lightPIN, LIGHT_OFF); // 初始灭灯
  Serial.begin(115200); // 初始化串口
  Serial.println("光敏模块初始化完成");
}

//读取光敏传感器状态并防抖
void readDOWithDebounce() {
  // 1. 防抖：统计「无遮挡=HIGH」的次数
  int highCount = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(SerPIN) == HIGH) { // 有遮挡=高电平
      highCount++;
    }
    delay(10); // 防抖延时
  }

  // 2. 判断光照状态：highCount≥2 → 有遮挡（光照不充足）
  bool isLightEnough = (highCount >= 2);

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


  Serial.printf("调试：SerPIN原始电平=%d，高电平次数=%d\n", digitalRead(SerPIN),count);
}

