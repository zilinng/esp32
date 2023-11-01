#include <WiFi.h>         //WiFi
#include <HTTPClient.h>   //瀏覽器
#include <ArduinoJson.h>  //請先安裝ArduinoJson程式庫
#include <Wire.h>
#include "U8g2lib.h"  //請下載u8g2程式庫
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

char ssid[] = "bala";                                                                                  //請修改為您連線的網路名稱
char password[] = "balalalala";                                                                        //請修改為您連線的網路密碼
char url[] = "http://data.moenv.gov.tw/api/v2/aqx_p_02?api_key=e8dd42e6-9b8b-43f8-991e-b3dee723a52d";  //讀取的網址及授權密碼

int LED1 = 5;   //RED
int LED2 = 16;  //GREEN
int LED3 = 15;  //BLUE


void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Wire.begin(21, 22);
  u8g2.begin();                                //初始化
  u8g2.enableUTF8Print();                      //啟用 UTF8字集
  u8g2.setFont(u8g2_font_unifont_t_chinese1);  //設定使用中文字形
  u8g2.setDrawColor(1);                        //設定顏色，我們是單色只有1
  u8g2.setFontPosTop();                        //座標從上開始
  u8g2.setFontDirection(0);                    //0不旋轉、1->90、2->180、3->270
  pinMode(36, INPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  //1.設定WiFi模式
  WiFi.mode(WIFI_STA);
  //2.啟動WiFi連線
  WiFi.begin(ssid, password);
  //3.檢查連線狀態
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
}

void loop() {
  //4.啟動網頁連線
  Serial.println("啟動網頁連線");
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  Serial.print("httpCode=");
  Serial.println(httpCode);
  //5.檢查網頁連線是否正常
  if (httpCode == HTTP_CODE_OK) {
    //6.取得網頁內容
    String payload = http.getString();
    //Serial.print("payload=");
    //7.將資料顯示在螢幕上
    //Serial.println(payload);
    //JSON格式解析
    DynamicJsonDocument AQIJson(payload.length() * 2);  //宣告一個JSON文件，名稱為AQIJson
    deserializeJson(AQIJson, payload);                  //解析網頁內容payload為JSON格式，存放在AQIJson內
    for (int i = 0; i <= AQIJson["records"].size(); i++) {
      // 瀏覽records內的所有紀錄，直到找到site=="橋頭"
      if (AQIJson["records"][i]["site"] == "中壢") {
        String AQI = AQIJson["records"][i]["pm25"];
        Serial.println("中壢PM2.5=" + AQI);
        int v;
        v = AQI.toInt();
             
        u8g2.clear();                                //顯示前清除螢幕
        u8g2.setCursor(0, 10);                       //移動游標
        u8g2.print(String("中壢PM2.5=：").c_str());  //寫入文字
        u8g2.print(String(AQI).c_str());
        u8g2.sendBuffer();  //送到螢幕顯示

        if (v >= 500) {
          analogWrite(LED3, 35);
          analogWrite(LED1, 126);
          analogWrite(LED2, 0);
        } else if (v >= 300) {
          analogWrite(LED1, 160);
          analogWrite(LED2, 32);
          analogWrite(LED3, 240);
        } else if (v >= 200) {
          analogWrite(LED3, 0);
          analogWrite(LED1, 255);
          analogWrite(LED2, 0);
        } else if (v >= 150) {
          analogWrite(LED3, 0);
          analogWrite(LED1, 255);
          analogWrite(LED2, 126);
        } else if (v >= 100) {
          analogWrite(LED3, 0);
          analogWrite(LED1, 255);
          analogWrite(LED2, 255);
        } else if (v >= 50) {
          analogWrite(LED3, 0);
          analogWrite(LED1, 255);
          analogWrite(LED2, 255);
        } else {
          analogWrite(LED1, 0);
          analogWrite(LED2, 255);
          analogWrite(LED3, 0);
        }
        break;
      }
    }
  }
  http.end();
  delay(10000);
}