int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;

#define MODE 2
int lastVal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switch(MODE){
    case 1: brightness(); break;
    case 2: evenOdd(); break;
    default: blinkSpeed(); break;
  }
}

void blinkSpeed(){
  int sensVal = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(sensVal);
  digitalWrite(ledPin, LOW);
  delay(sensVal);
}

void brightness(){
  int sensVal = analogRead(sensorPin);
  if(sensVal != lastVal){
    analogWrite(ledPin, sensVal/4);
    lastVal = sensVal;
  }
}

void evenOdd(){
  int sensVal = analogRead(sensorPin);
  if(sensVal % 2 == 0){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
