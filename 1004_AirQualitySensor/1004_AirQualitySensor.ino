//#include "analogWrite.h" //0~255
int LED1 = 15;//RED
int LED2=2;//GREEN
int LED3=0;//BLUE
int lightPin = 36;

void setup() {
  // put your setup code here, to run once:
 pinMode(LED1,OUTPUT);
 pinMode(LED2,OUTPUT);
 pinMode(LED3,OUTPUT);
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = analogRead(lightPin);  //0~3.3v -> 0~4095
  Serial.println(v);
  delay(100);
  if (v >= 3000) {
  analogWrite(LED3, 255);
  analogWrite(LED1, 255);
  analogWrite(LED2, 0);   
  } else if (v >= 1500) {
    analogWrite(LED1, 255);
    analogWrite(LED2, 0);
    analogWrite(LED3, 0);   
  } else if (v >= 500) {
    analogWrite(LED3, 0);
    analogWrite(LED1, 255);
    analogWrite(LED2, 255);   
  } else {
    analogWrite(LED1,0);
    analogWrite(LED2, 255);
    analogWrite(LED3,0);  
    }


  /*analogWrite(LED1, 255);
  analogWrite(LED2, 0);
  analogWrite(LED3, 0);
  delay(1000);*/
  /*analogWrite(LED1,0);
  analogWrite(LED2, 255);
  analogWrite(LED3,0);
  delay(1000);*/
  /*analogWrite(LED1,0);
  analogWrite(LED2,0);
  analogWrite(LED3, 255);
  delay(1000);*/
  /*analogWrite(LED3, 0);
  analogWrite(LED1, 255);
  analogWrite(LED2, 255);
  delay(1000);*/
  /*analogWrite(LED3, 255);
  analogWrite(LED1, 255);
  analogWrite(LED2, 0);
  delay(1000);*/
  /*analogWrite(LED1, 255);
  analogWrite(LED2, 50);
  analogWrite(LED3, 80);
  delay(1000);*/
/*for (int i=0;i<=255;i++){
  analogWrite(LED1,i);
  delay(10);
}*/

/*for (int i=255;i>=0;i--){
  analogWrite(LED1,i);
  delay(10);
}*/
}
