void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);  //綠色LED
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);  //亮燈:數位寫入4號腳高電位(HIGH/1/true)
  delay(1000);            //1000ms=1s
  digitalWrite(4, LOW);   //關燈
  delay(1000);
}
