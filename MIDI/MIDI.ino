//#include <MIDI.h>
#include <FastLED.h>

#define DATA_PIN    11
#define NUM_LEDS    10
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte pitch, byte velocity) {
    //leds[velocity] = CRGB::Red;
    //FastLED.show();
    //FastLED.delay(100);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
    //leds[channel] = CRGB::Black;
    //FastLED.show();
    //FastLED.delay(100);
}

void resetLEDS(){
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      FastLED.show();
   }
}

void colorLEDs(){
    for(int i = 0; i < NUM_LEDS; i++) {
      if(1%3 == 0) {
        leds[i] = CRGB::Red;
        FastLED.show();
      } else if(1%3 == 1){
        leds[i] = CRGB::Green;
        FastLED.show();
      } else {
        leds[i] = CRGB::Blue;
        FastLED.show();
      }
   }
}


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    //FastLED.setBrightness(  BRIGHTNESS );
    //resetLEDS();
    colorLEDs();
    
    //MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
    //MIDI.setHandleNoteOff(handleNoteOff);
    //MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
    //MIDI.read();
}
