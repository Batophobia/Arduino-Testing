const int button1 = 2;
const int button2 = 3;
const int ledPin =  13;

int def = HIGH;
bool btn2Up = true;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void loop() {
  handleButton(1);
  handleButton(2);
}

void handleButton(int num){
  int buttonState;
  if(num == 2) {
    buttonState = digitalRead(button2);
    if (buttonState == LOW && btn2Up) {
      Serial.println("Btn 2 Pressed");
      btn2Up = false;
      if(def == HIGH) def = LOW;
      else def = HIGH;
    } else if(buttonState == HIGH) {
      btn2Up = true;
    }
  } else {
    buttonState = digitalRead(button1);
    if (buttonState == HIGH) {
      digitalWrite(ledPin, def);
    } else {
      Serial.println("Btn 1 Pressed");
      digitalWrite(ledPin, !def);
    }
  }
}
