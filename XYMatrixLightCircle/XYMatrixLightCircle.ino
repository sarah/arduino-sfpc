#include <FastLED.h>

#define LED_PIN  6
#define BAUD_RATE 57600
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define BRIGHTNESS 10         

int inByte = 0;  // incoming serial byte
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;
int x = kMatrixWidth; // might not be using
float radiusOffset = 7.5;
const bool    kMatrixSerpentineLayout = false; // Param for different pixel layouts
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

void loop()
{
    TestOrientation();
    FastLED.show();
    
}

void PurrLights(){
  while(Serial.available() > 0){
    inByte = Serial.read();
    float radius = (float(inByte)/255.0)*6.0;
    LightAreaCircle(radius);
    FastLED.show();
  }
}

void TestOrientation(){
  // Four corners
  leds[ XYsafe( 0,0)] = CRGB(255,0,0);
  leds[ XYsafe( 15,0)] = CRGB(255,0,0);
//  leds[ XYsafe( 0,15)] = CRGB(255,0,0);
//  leds[ XYsafe( 15,15)] = CRGB(255,0,0);
}
void LightAreaCircle(float input){
  int w = kMatrixWidth;
  int h = kMatrixHeight;
  float radius = input;
  for(int x=0; x<w; x++){
    for(int y=0; y<h; y++){
      int pos = x *w + y;
      float xf = (float)x;
      float yf = (float)y;
      float dist = sqrt( ( xf-radiusOffset)*( xf-radiusOffset) + (yf-radiusOffset)*(yf-radiusOffset));
//      Serial.println(radius);
      if(dist < radius){
        float bright = 255.0 - (dist / max(radius,.001)) * 255.0; // diff shades of grey -> white
        leds[ XYsafe( x,y)] = CHSV(255,5,bright);
      } else {
        leds[ XYsafe( x,y)] = CHSV(0,1,0);
      }
    }
  }
}

void DrawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
{
  byte lineStartHue = startHue8;
  byte lineStartValue = 0;
  for( byte y = 0; y < kMatrixHeight; y++) {
    lineStartHue += yHueDelta8;
    byte pixelHue = lineStartHue; 
    byte pixelValue =    lineStartValue;  
    for( byte x = 0; x < kMatrixWidth; x++) {
      pixelHue += xHueDelta8;
      pixelValue += xHueDelta8;
//      leds[ XY(x, y)]  = CHSV( pixelHue, 255, 255);
//leds[ XY(x, y)]  = CHSV( 255, 0, pixelValue);
    }
  }
}


void setup() {
  Serial.begin(BAUD_RATE);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  
  return i;
}

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

