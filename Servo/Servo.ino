#include <Servo.h>

Servo servo;
int pos = 0;

void setup() {
  servo.attach(9);
}

void loop() {
  circle();
  randomized();
  extreme();
}

void circle(){
  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);
    delay(10);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(10);
  }
}

void randomized(){
  pos = random(0,180);
  servo.write(pos);
  delay(500);
}

void extreme(){
  servo.write(180);
  delay(500);
  servo.write(0);
  delay(500);
}
