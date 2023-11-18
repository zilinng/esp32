#include <WiFi.h>
#include <HTTPClient.h>
#include <SimpleDHT.h>

char ssid[] = "bala"; //請修改為您連線的網路名稱
char password[] = "balalalala"; //請修改為您連線的網路密碼
String url = "http://api.thingspeak.com/update?api_key=NYEOSOYATARXMAW9"; //PM2.5的網址
//                                        問號: 參數傳遞開始           &:參數串接
//String字串 char字元陣列(長度需固定)
int pinDHT11 = 4;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  //1.設定WiFi模式
  WiFi.mode(WIFI_STA);
  //2.啟動WiFi連線
  WiFi.begin(ssid, password); //裡面一定要放char
  //3.檢查連線狀態
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
}

void loop() {

// start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  //
  String newurl = url+"&field1="+(String)temperature+"&field2="+(String)humidity;  

  //4.啟動網頁連線
  Serial.println("啟動網頁連線");
  HTTPClient http;
  http.begin(newurl);
  int httpCode = http.GET();
  Serial.print("httpCode=");
  Serial.println(httpCode);
  //5.檢查網頁連線是否正常
  if (httpCode == HTTP_CODE_OK) {
    //6.取得網頁內容
    String payload = http.getString();
    Serial.print("payload=");
    //7.將資料顯示在螢幕上
    Serial.println(payload);
  }
  //8.關閉網頁連線
  http.end();
  delay(15000);
}
