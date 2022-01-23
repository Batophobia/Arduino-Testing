int pins[] = {2,3,4,5,6,7,8,9};
int arrLength;

void setup() {
  Serial.begin(9600);
  arrLength = sizeof(pins) / sizeof(int);
  Serial.print(arrLength);
  Serial.println();
  for(int i = 0; i < arrLength; i++){
    pinMode(pins[i],OUTPUT);
  }
}

void loop() {
  sequence();
  fill();
  reset();
  pulse();
  reset();
  randomized();
  reset();
}

void sequence(){
  int timeDelay = 250;
  for(int i = 0; i < arrLength; i++){
    digitalWrite(pins[i],HIGH);
    delay(timeDelay);
    digitalWrite(pins[i],LOW);
  }
}

void fill(){
  int timeDelay = 100;
  for(int i = 0; i < arrLength; i++){
    delay(timeDelay * (i+1));
    digitalWrite(pins[i],HIGH);
  }
  delay(250);
}

void randomized(){
  for(int i = random(8,20); i >= 0; i--){
    int idx = random(0,arrLength);
    digitalWrite(pins[idx],HIGH);
    delay(random(200,500));
    digitalWrite(pins[idx],LOW);
  }
}

void pulse(){
  int timeDelay = 5;
  for(int b = 0; b < 255; b++){
    for(int i = 0; i < arrLength; i++){
      analogWrite(pins[i],b);
    }
    delay(timeDelay);
  }
  for(int i = 0; i < arrLength; i++){
    analogWrite(pins[i],0);
  }
}

void reset(){
  for(int i = 0; i < arrLength; i++){
    digitalWrite(pins[i],LOW);
  }
}
