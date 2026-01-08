#ifndef KEY_H
#define KEY_H

#include <Arduino.h>

// 按键引脚定义
#define KEY1_PIN 15  // 切换页面1
#define KEY2_PIN 16  // 切换页面2
#define KEY3_PIN 5  // 切换页面3

// 页面枚举（方便管理）
typedef enum {
  PAGE_ENV = 0,    // 环境数据页（默认）
  PAGE_WIFI = 1,   // WiFi信息页
  PAGE_DEBUG = 2   // 调试信息页
} DisplayPage;

// 全局当前页面（供OLED任务和按键任务共享）
extern DisplayPage currentPage;

// 函数声明
void setupKeys();       // 初始化按键
void readKeys();        // 读取按键（防抖）

#endif