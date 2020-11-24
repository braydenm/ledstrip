#include "FastLED16.h"
#define NUM_LEDS 5*72
#define DATA_PIN 7
#define CLOCK_PIN 5
CRGB leds[NUM_LEDS];
void setup() { FastLED.addLeds<HD108, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);}
void loop() {
  leds[0] = CRGB::White; FastLED.show(); delay(100);
  leds[0] = CRGB::Black; FastLED.show(); delay(100);
}
