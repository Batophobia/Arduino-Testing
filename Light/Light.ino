int lightPin = 0;
int ledPin = 9;

#define MODE 2

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switch(MODE){
    case 1: inverted(); break;
    case 2: threshold(); break;
    default: standard(); break;
  }
}

void standard() {
  int lightLevel = analogRead(lightPin);
  lightLevel = map(lightLevel, 0, 900, 0, 255); 
  lightLevel = constrain(lightLevel, 0, 255);
  analogWrite(ledPin, lightLevel);
}

void inverted() {
  int lightLevel = analogRead(lightPin);
  lightLevel = map(lightLevel, 0, 900, 0, 255); 
  lightLevel = constrain(lightLevel, 0, 255);
  analogWrite(ledPin, 255 - lightLevel);
}

void threshold() {
  int lightLevel = analogRead(lightPin);
  lightLevel = map(lightLevel, 0, 900, 0, 255); 
  lightLevel = constrain(lightLevel, 0, 255);
  if(lightLevel > 120) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}
