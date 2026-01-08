#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>


// 只声明变量（extern表示“变量在其他文件定义”）
extern const char* ssid;
extern const char* password;
extern const int pinLED;

// 函数声明
void setupWiFi();
bool isWiFiDisconnected();
void checkWiFiConnection();
void wifiTask(void *param);

#endif // WIFI_MANAGER_H