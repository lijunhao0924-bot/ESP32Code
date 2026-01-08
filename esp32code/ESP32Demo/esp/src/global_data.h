#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// 声明全局变量（供所有文件使用）
extern float g_temp;       // 温度
extern float g_hum;        // 湿度
// 舵机任务句柄（由 main.cpp 定义）
extern TaskHandle_t servoTaskHandle;

#endif