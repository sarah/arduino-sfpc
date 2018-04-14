#include <FastLED.h>

#define LED_PIN  6
#define BAUD_RATE 57600
#define BUFFER_SIZE 192
#define UNUSED -1
#define OK_MSG "OK"
#define BREAK_CHAR 255

// matrix
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define BRIGHTNESS 5

// Params for width and height
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 8;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = false;

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


#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

// SERIAL
int inByte = 0;                 // incoming serial byte
int frameBuffer[BUFFER_SIZE]; 
int ptr = 0; 
int width = kMatrixWidth;

// Demo that USES "XY" follows code below

void loop()
{
//    PurrLights();
      digitalWrite(13, HIGH);
      DrawScreenFromOf();
      digitalWrite(13, LOW);
//      delay(3000);
//    FastLED.show();
}

void DrawScreenFromOf(){

  while(Serial.read() != BREAK_CHAR);

  while(true) {
    while(!Serial.available());    
    inByte = int(Serial.read());
      if(inByte != BREAK_CHAR){
         frameBuffer[ptr] = inByte; // adding bytes to array
         ptr++;
      } else {
        DrawOfFrame();
        resetBuffer();   
        return;
      }
  }
}
void PurrLights(){
  while(Serial.available() > 0){
    inByte = Serial.read();
    float radius = (float(inByte)/255.0)*6.0;
    LightAreaCircle(radius);
  }
}
void DrawOfFrame(){
  int w = kMatrixWidth; // 8
  int h = kMatrixHeight; // 8
  
  for(int x=0; x<w; x++){
    for(int y=0; y<h; y++){
        int redPixelIdx = ((y*w)+x)*3;
        int r = frameBuffer[redPixelIdx];
        int g = frameBuffer[redPixelIdx+1];
        int b = frameBuffer[redPixelIdx+2];
        leds[ XYsafe( x,y)] = CRGB(r,g,b);
    }
  }
  FastLED.show();
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
      float dist = sqrt( ( xf-3.5)*( xf-3.5) + (yf-3.5)*(yf-3.5));
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
  pinMode(13, OUTPUT);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}

void initializeBuffer(){
  for(int i=0; i< BUFFER_SIZE; i++){
    frameBuffer[i] = UNUSED;
  }
}

void resetBuffer(){
  initializeBuffer();
  ptr = 0;
}
