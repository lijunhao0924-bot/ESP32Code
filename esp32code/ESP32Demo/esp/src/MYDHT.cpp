#include "MYDHT.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include "global_data.h" // 包含全局变量头文件（仅声明，不定义）

SemaphoreHandle_t dhtDataMutex = NULL;
DHT dht(DHTPIN, DHTTYPE);

void initDHTMutex() {
  if (dhtDataMutex == NULL) {
    dhtDataMutex = xSemaphoreCreateMutex();
    if (dhtDataMutex == NULL) {
      Serial.println("DHT互斥锁创建失败！");
    }
  }
}

float readDHTTemp() {
  float temp = -999.0;
  temp = dht.readTemperature();
  return isnan(temp) ? -999.0 : temp;
}

float readDHTHum() {
  float hum = -999.0;
  hum = dht.readHumidity();
  return isnan(hum) ? -999.0 : hum;
}

void sensorTask(void *param) {
  dht.begin();
  Serial.println("DHT11 传感器初始化完成");
  
  while (true) {
    if (dhtDataMutex != NULL) {
      xSemaphoreTake(dhtDataMutex, portMAX_DELAY);
    }
    
    // 更新全局变量
    g_temp = readDHTTemp();
    g_hum = readDHTHum();
    
    if (g_temp != -999.0 && g_hum != -999.0) {
      Serial.printf("温度: %.2f °C, 湿度: %.2f %%\n", g_temp, g_hum);
    } else {
      Serial.println("读取温湿度失败！");
    }
    
    if (dhtDataMutex != NULL) {
      xSemaphoreGive(dhtDataMutex);
    }
    
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}