#define DELAY 10

int ledDigitalOne[] = {9, 10, 11};

int r=0, g=0, b=255;
int dr=0, dg=0, db=0;

void setup(){
  for(int i = 0; i < 3; i++){
    pinMode(ledDigitalOne[i], OUTPUT);
  }
}

void loop(){
   fading();
   delay(DELAY);
}

void fading(){
  r = r + dr;
  g = g + dg;
  b = b + db;
  
  if(r<=0) { dr=0; }
  if(g<=0) { dg=0; }
  if(b<=0) { db=0; }
  
  if(r>=255) { dr=0; }
  if(g>=255) { dg=0; }
  if(b>=255) { db=0; }

  if(r >= 255 && b >= 255) db = -1;
  else if(r >= 255 && g >= 255) dr = -1;
  else if(g >= 255 && b >= 255) dg = -1;
  
  else if(r <= 0 && b <= 0) db = 1;
  else if(r <= 0 && g <= 0) dr = 1;
  else if(g <= 0 && b <= 0) dg = 1;

  byte tmp[] = {r, g, b};
  setColor(ledDigitalOne, tmp);
}

void setColor(int* led, const byte* color){
  for(int i = 0; i < 3; i++){
    analogWrite(led[i], 255 - color[i]);
  }
}
