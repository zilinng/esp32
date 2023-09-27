void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(17, INPUT);
  pinMode(16, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = digitalRead(17);
  if (v == 1) {
    digitalWrite(16, 1);
    delay(100);
    digitalWrite(16, 0);
  }
  Serial.println(v);
  delay(500);
}
