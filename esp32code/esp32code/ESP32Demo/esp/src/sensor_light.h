#ifndef SENSOR_LIGHT_H
#define SENSOR_LIGHT_H
#include <Arduino.h>
#define lightPIN 14
#define SerPIN 34
extern bool lightStatus;
const int LIGHT_ON = HIGH;   // 光照充足时DO输出低电平
const int LIGHT_OFF = LOW;
void SetupLDR();
void readDOWithDebounce();  




#endif