#define FASTLED_INTERNAL
#include <FastLED.h>
#define NUM_LEDS 64
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {

  leds[0] = CHSV( 224, 187, 255);
//  // put your main code here, to run repeatedly:
//   for(int dot = 0; dot < NUM_LEDS; dot++) { 
//            leds[dot] = CRGB::Blue;
//            FastLED.show();
//            // clear this led for the next time around the loop
//            leds[dot] = CRGB::Black;
//            delay(30);
//        }
}
