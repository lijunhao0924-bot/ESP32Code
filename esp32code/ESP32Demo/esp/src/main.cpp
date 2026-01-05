#include <Arduino.h>
#include "WiFiManager.h"
#include "MYDHT.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sensor_light.h"
#include "OLED.h"
#include "key.h"  // 引入按键头文件

// 原有全局变量（不变）
float g_temp = 0.0;
float g_hum = 0.0;
TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t oledTaskHandle = NULL;
// 新增：按键任务句柄
TaskHandle_t keyTaskHandle = NULL;

// 修改OLED任务：使用新的多页面显示函数
void oledTask(void *param) {
  while (true) {
    showCurrentPage(g_temp, g_hum, lightStatus);  // 替换原有showEnvData
    vTaskDelay(pdMS_TO_TICKS(500));  // 刷新频率提高到500ms，响应更快
  }
}

// 新增：按键任务函数
void keyTask(void *param) {
  while (true) {
    readKeys();  // 循环读取按键
    vTaskDelay(pdMS_TO_TICKS(20));  // 按键扫描频率20ms
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  SetupLDR();
  setupOLED();
  setupKeys();  // 初始化按键
  // 初始化时用默认值显示
  showCurrentPage(g_temp, g_hum, lightStatus);  // 替换原有showEnvData
  Serial.println("========== ESP32 FreeRTOS 启动 ==========");

  initDHTMutex();

  // 原有任务创建（不变）
  xTaskCreatePinnedToCore(
    sensorTask,        
    "SensorTask",      
    16384,             
    NULL,              
    3,                 
    &sensorTaskHandle,
    0                  
  );

  xTaskCreatePinnedToCore(
    wifiTask,          
    "WiFiTask",        
    16384,             
    NULL,              
    1,                 
    &wifiTaskHandle,
    0                  
  );

  xTaskCreatePinnedToCore(
    oledTask,          
    "OledTask",        
    4096,              
    NULL,              
    2,                 
    &oledTaskHandle,
    0                  
  );

  // 新增：创建按键任务
  xTaskCreatePinnedToCore(
    keyTask,           
    "KeyTask",         
    2048,              // 按键任务栈大小不需要太大
    NULL,              
    2,                 // 优先级和OLED任务一致
    &keyTaskHandle,
    1                  // 绑定到核心1（分散负载）
  );
}

void loop() {
  // 原有逻辑（不变）
  readDOWithDebounce();
  vTaskDelay(pdMS_TO_TICKS(1000));
}