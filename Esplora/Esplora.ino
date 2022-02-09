#include <FastLED.h>
#include <Esplora.h>

#define DELAY 16 // approx. 60 fps
#define CAPTURE_NOTE 550
#define LOSE_NOTE 100
#define BUFFER 10

#define DATA_PIN   11
#define NUM_LEDS    40
#define LED_TYPE    WS2811
#define COLOR_ORDER BRG
CRGB leds[NUM_LEDS];

boolean buttonStates[8];
const byte buttons[] = {
  JOYSTICK_DOWN,
  JOYSTICK_LEFT,
  JOYSTICK_UP,
  JOYSTICK_RIGHT,
  SWITCH_RIGHT,
  SWITCH_LEFT,
  SWITCH_UP,
  SWITCH_DOWN,
};

int plrPos = 0;
int plrClr = 0;
int plrBright = 0;
int plrSat = 255;

#define MAX_ENEMY 3
#define SPAWN_RATE 120

int enemyPos[] = { -1, -1, -1 };
int enemyClr[] = { -1, -1, -1 };
int nextSpawn = SPAWN_RATE;

bool isPlaying = false;
int idleIdx = 0;
int idleDir = 1;

void resetLEDS() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
}

void setupLEDs() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  resetLEDS();
  FastLED.show();
}

void setupGame() {
  isPlaying = false;
  setupEnemies();
  setupPlayer();
  idleIdx = 0;
  idleDir = 1;
}

void setupEnemies() {
  for(int i = MAX_ENEMY; --i >= 0;) {
    enemyPos[i] = -1;
    enemyClr[i] = -1;
  }
  nextSpawn = SPAWN_RATE;
}

void setupPlayer() {
  plrPos = round(NUM_LEDS/2);
}

void setup() {
  //Serial.begin(19200);
  setupLEDs();
  setupGame();
}

void loop() {
  Esplora.noTone();
  handleButtons();
  handleSlider();
  handleLightSensor();
  handleTemp();
  
  if(isPlaying) {
    enemySpawner();
    resetLEDS();
    drawPlayer();
    drawEnemies();
  } else {
    idle();
  }
  FastLED.show();
  
  //test();
  delay(DELAY);
}

void idle(){
  leds[idleIdx] = CHSV(0, 0, 0);
  idleIdx += idleDir;
  if(idleIdx <= 0 || idleIdx >= NUM_LEDS - 1) idleDir *= -1;
  leds[idleIdx] = CHSV(plrClr, plrSat, plrBright);
}

void drawPlayer() {
  leds[plrPos] = CHSV(plrClr, plrSat, plrBright);
}

void drawEnemies() {
  for(int i = MAX_ENEMY; --i >= 0;) {
    if(enemyPos[i] > -1)
      leds[enemyPos[i]] = CHSV(enemyClr[i], plrSat, plrBright);
  }
}

void enemySpawner() {
  //Serial.print("Next spawn: "); Serial.println(nextSpawn);
  if(nextSpawn-- > 0) return;

  //Serial.println("SPAWN ENEMY");
  nextSpawn = SPAWN_RATE;
  for(int i = MAX_ENEMY; --i >= 0;) {
    if(enemyPos[i] > -1) continue;
    
    int t = random(0,2);
    if(plrPos < 4) t = 1;
    else if(plrPos > NUM_LEDS-4) t = -1;
    else t = (t * 2) - 1; // Get 1 or -1
    
    t = t * random(2,4);

    bool badLoc = false;
    for(int j = 0; j < MAX_ENEMY; j++)
      if(enemyPos[j] == plrPos + t) badLoc = true;
    if(badLoc) continue;
    
    enemyPos[i] = plrPos + t;

    // Didn't want to deal with wrap-around maths
    t = random(BUFFER, 255 - BUFFER);
    enemyClr[i] = t;
    return;
  }
}

void handleSlider() {
  int slider = Esplora.readSlider();
  plrClr = slider / 4;
  //enemyClr = (plrClr + 128) % 256;
}

void handleLightSensor() {
  int light = Esplora.readLightSensor();
  int brightness = map(light, 0, 1024, 0, 128);
  brightness = constrain(brightness, 0, 128);
  plrBright = 255 - brightness;
}

void handleTemp() {
  int temp = Esplora.readTemperature(DEGREES_F);
  //Serial.print("Temp: "); Serial.println(temp);
  int saturation = map(temp, 65, 85, 125, 255);
  saturation = constrain(saturation, 125, 255);
  plrSat = saturation;
}

void handleButtons() {
  for (byte thisButton = 0; thisButton < 8; thisButton++) {
    boolean lastState = buttonStates[thisButton];
    boolean newState = Esplora.readButton(buttons[thisButton]);
    
    if (lastState != newState) {
      if (newState == PRESSED) buttonPress(thisButton, true);
      else if (newState == RELEASED) buttonPress(thisButton, false);
    }

    buttonStates[thisButton] = newState;
  }
}

void buttonPress(byte button, bool pressed) {
  if(!isPlaying) {
    if(pressed && ( buttons[button] == SWITCH_UP || buttons[button] == SWITCH_DOWN ))
      isPlaying = true;
    return;
  }
  switch(buttons[button]) {
    case JOYSTICK_DOWN:
    case JOYSTICK_RIGHT:
    case SWITCH_RIGHT:
      if(pressed && plrPos > 0) plrPos--;
      break;
    case JOYSTICK_UP:
    case JOYSTICK_LEFT:
    case SWITCH_LEFT:
      if(pressed && plrPos < NUM_LEDS - 1) plrPos++;
      break;
    case SWITCH_DOWN:
      break;
    case SWITCH_UP:
      break;
  }
  checkHit();
}

void checkHit() {
  for(int i = MAX_ENEMY; --i >= 0;) {
    if(plrPos != enemyPos[i]) continue;

    //Serial.print("Player: ");Serial.print(plrClr);Serial.print(" - Enemy: ");Serial.println(enemyClr[i]);

    if(enemyClr[i] - BUFFER <= plrClr && plrClr <= enemyClr[i] + BUFFER) return destroy(i);
    else return lose();
  }
}

void destroy(int idx) {
  Esplora.tone(CAPTURE_NOTE);
  enemyPos[idx] = -1;
  enemyClr[idx] = -1;
}

void lose() {
  for(int i = NUM_LEDS; --i >= 0;) {
    Esplora.tone(LOSE_NOTE + i);
    leds[i] = CHSV(0, plrSat, plrBright);
    FastLED.show();
    delay(30);
  }  
  Esplora.noTone();

  
  setupGame();
  //Serial.println("Game Over");
}
