#include <WiFi.h>
#include <HTTPClient.h>
#include <SimpleDHT.h>
//請修改以下參數--------------------------------------------
char ssid[] = "bala"; //請修改為您連線的網路名稱
char password[] = "balalalala"; //請修改為您連線的網路密碼
//將原本ThingSpeak的網址換成ifttt網址
String url = "http://maker.ifttt.com/trigger/class215/with/key/nvOj_pUuqp23DtfEMDpmwOnm7Bu0w1aJzDMqNS2ud9X";

int pinDHT11 = 4;//假設DHT11 接在GPIO4，接線圖請參考P74
//---------------------------------------------------------
SimpleDHT11 dht11(pinDHT11);//宣告SimpleDHT11物件

void setup()
{
  Serial.begin(115200);
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
}

void loop()
{
  //start working...
  Serial.println("=============");
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("溫度計讀取失敗，錯誤碼="); Serial.println(err); delay(1000);
    return;
  }
  //讀取成功，將溫濕度顯示在序列視窗
  Serial.print("溫度計讀取成功: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");
  //開始傳送到thingspeak
  Serial.println("啟動網頁連線");
  HTTPClient http;
  //將溫度及濕度以HTTP Get參數方式補入網址後方
  String url1 = url + "?value1=" + String(temperature) + "&value2=" + String(humidity); //thinkspeak是用field1 field2存
  //http client取得網頁內容
  http.begin(url1);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)      {
    //讀取網頁內容到payload
    String payload = http.getString();
    //將內容顯示出來
    Serial.print("網頁內容=");
    Serial.println(payload);
  } else {
    //讀取失敗
    Serial.println("網路傳送失敗");
  }
  http.end();
  delay(20000);//休息20秒
}