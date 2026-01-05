#include "OLED.h"
#include "MYDHT.h"
#include "sensor_light.h"
#include "global_data.h"  // 新增：引入全局变量声明
#include "WiFiManager.h"  // 若用到WiFi相关变量也需引入
#include "KEY.h"  // 新增：引入按键头文件
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

// 以下原有代码不变...
void setupOLED() {
  Wire.begin(21, 22);
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED初始化失败！"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("OLED初始化成功！");
  display.display();
  delay(1000);
}

// 原有showEnvData函数不变...
void showEnvData(float temp, float hum, bool lightStatus) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("Temp: %.1f °C", temp);
  display.setCursor(0, 16);
  display.printf("Hum: %.1f %%", hum);
  display.setCursor(0, 32);
  display.print("Light: ");
  display.print(lightStatus ? "Enough" : "Not Enough");
  display.display();
}

// 新增的WiFi页函数（若用到WiFi变量需确保头文件引入）
void showWiFiPage() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi Status: ");
  display.print(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
  
  display.setCursor(0, 16);
  display.print("SSID: ");
  display.print(WiFi.SSID());
  
  display.setCursor(0, 32);
  display.print("IP: ");
  display.print(WiFi.localIP().toString());
  
  display.display();
}

// 修复调试页：现在g_temp/SerPIN等变量可被识别
void showDebugPage() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("DHT Temp: %.1f °C", g_temp);
  
  display.setCursor(0, 16);
  display.printf("Light PIN: %d", digitalRead(SerPIN));
  
  display.setCursor(0, 32);
  display.printf("Page: %d", currentPage);
  
  display.display();
}

void showCurrentPage(float temp, float hum, bool lightStatus) {
  switch (currentPage) {
    case PAGE_ENV:
      showEnvData(temp, hum, lightStatus);
      break;
    case PAGE_WIFI:
      showWiFiPage();
      break;
    case PAGE_DEBUG:
      showDebugPage();
      break;
    default:
      showEnvData(temp, hum, lightStatus);
      break;
  }
}