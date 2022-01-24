int temperaturePin = 0; //TMP36's Vout (sense) pin
                        //resolution is 10 mV / degree centigrade 
                        //(500 mV offset) to make negative temperatures an option
int led = 9;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}
 
void loop() {
  float temperature = getVoltage(temperaturePin);
  Serial.print(temperature); Serial.println(" V");
  temperature = (((temperature - .5) * 100) * 1.8) + 32;
  Serial.print(temperature); Serial.println(" deg F");
  
  if(temperature < 68) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  
  delay(500);
}

float getVoltage(int pin){
  return (analogRead(pin) * .004882814);
}
