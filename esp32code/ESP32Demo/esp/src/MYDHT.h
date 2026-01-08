#ifndef MYDHT_H
#define MYDHT_H

#include <Arduino.h>
#include <DHT.h>

// 硬件配置
#define DHTPIN 4
#define DHTTYPE DHT11
extern DHT dht;


float readDHTTemp();
float readDHTHum();
void initDHTMutex();


// 只保留核心函数声明
void sensorTask(void *param);

#endif