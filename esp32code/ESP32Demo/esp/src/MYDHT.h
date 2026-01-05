#ifndef MYDHT_H
#define MYDHT_H

#include <Arduino.h>
#include <DHT.h>

// 硬件配置（确认你的DHT11接的是GPIO4，不是就改）
#define DHTPIN 4
#define DHTTYPE DHT11
extern DHT dht;

// 核心读数函数（极简，无多余逻辑）
float readDHTTemp();
float readDHTHum();
void initDHTMutex();


// 只保留核心函数声明
void sensorTask(void *param);

#endif