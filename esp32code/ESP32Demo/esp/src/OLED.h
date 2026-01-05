#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "key.h"  // 引入页面枚举

// 原有常量定义（不变）
#define OLED_WIDTH  128  
#define OLED_HEIGHT 64   
#define OLED_ADDR   0x3C 
#define OLED_RESET  -1   

extern Adafruit_SSD1306 display;

// 原有函数声明（不变）
void setupOLED();        
void showEnvData(float temp, float hum, bool lightStatus);

// 新增：多页面显示函数
void showWiFiPage();     // WiFi信息页
void showDebugPage();    // 调试信息页
void showCurrentPage(float temp, float hum, bool lightStatus); // 根据当前页面显示对应内容

#endif