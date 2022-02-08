#include <FastLED.h>
#include <Esplora.h>

#define DELAY 16 // approx. 60 fps

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
int deltSat = -1;

int enemyClr = 128;

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

void setup() {
  setupLEDs();
}

void loop() {
  handleButtons();
  handleSlider();
  handleLightSensor();
  test();
  delay(DELAY);
}

void test() {
  resetLEDS();
  // Player test
  leds[plrPos] = CHSV(plrClr, plrSat, plrBright);
  FastLED.show();

  // Enemy test
  leds[2] = CHSV(enemyClr, plrSat, plrBright);
  FastLED.show();

  plrSat += deltSat;
  if(plrSat <= 0 || plrSat >= 255) deltSat *= -1;
}

void handleSlider() {
  int slider = Esplora.readSlider();
  plrClr = slider / 4;
  enemyClr = (plrClr + 128) % 256;
}

void handleLightSensor() {
  int light = Esplora.readLightSensor();
  int brightness = map(light, 0, 1024, 0, 128);
  brightness = constrain(brightness, 0, 128);
  plrBright = 255 - brightness;
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
}
