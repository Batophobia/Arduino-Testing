int motorPin = 9;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  test01();
  test02();
  test03();
}

void test01(){
  int timeOn = 2000;
  int timeOff = 1000;

  digitalWrite(motorPin, HIGH);
  delay(timeOn);
  digitalWrite(motorPin, LOW);
  delay(timeOff);
}

void test02(){
  int spdOn = 200;
  int timeOn = 3000;
  int spdOff = 50;
  int timeOff = 2000;

  analogWrite(motorPin, spdOn);
  delay(timeOn);
  analogWrite(motorPin, spdOff);
  delay(timeOff);
}

void test03(){
  int delayTime = 50;
  for(int i = 0; i < 256; i++){
    analogWrite(motorPin, i);
    delay(delayTime);
  }
  for(int i = 255; i >= 0; i--){
    analogWrite(motorPin, i);
    delay(delayTime);
  }
}
