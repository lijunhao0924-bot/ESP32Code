#include "WiFiManager.h"

const char* ssid = "0924";  
const char* password = "1234567890";
const int pinLED = 2;                 

void setupWiFi() {
    Serial.println("正在连接WiFi中");
    WiFi.begin(ssid, password);
    unsigned long start = millis();
    pinMode(pinLED, OUTPUT);
    
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(pinLED, !digitalRead(pinLED));
        delay(500);
        if (millis() - start > 10000) {
            digitalWrite(pinLED, LOW);
            return;
        }
    }
    
    Serial.println("连接成功");
    Serial.print("WiFi名称: ");
    Serial.println(WiFi.SSID());
    Serial.print("WiFi密码: ");
    Serial.println(password);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(pinLED, HIGH);
}

bool isWiFiDisconnected() {
  return WiFi.status() != WL_CONNECTED;
}

void checkWiFiConnection() {
    if (isWiFiDisconnected()) {
        setupWiFi();
    }
}

void wifiTask(void *param) {
    while (true) {
        checkWiFiConnection();
        vTaskDelay(5000 / portTICK_PERIOD_MS); // 每5秒检查一次连接
    }
}