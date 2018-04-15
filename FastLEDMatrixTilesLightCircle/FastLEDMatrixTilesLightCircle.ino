#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix

// Change the next defines to match your matrix type and size
#define DATA_PIN            6

#define COLOR_ORDER         GRB
#define CHIPSET             WS2811

#define MATRIX_TILE_WIDTH   8 // width of EACH NEOPIXEL MATRIX (not total display)
#define MATRIX_TILE_HEIGHT  8 // height of each matrix

#define MATRIX_TILE_H       2  // number of matrices arranged horizontally
#define MATRIX_TILE_V       2  // number of matrices arranged vertically

#define MATRIX_WIDTH        (MATRIX_TILE_WIDTH*MATRIX_TILE_H)
#define MATRIX_HEIGHT       (MATRIX_TILE_HEIGHT*MATRIX_TILE_V)

#define MATRIX_TYPE        (MTX_MATRIX_TOP | MTX_MATRIX_LEFT | MTX_MATRIX_ROWS | MTX_MATRIX_ZIGZAG | MTX_TILE_TOP | MTX_TILE_LEFT | MTX_TILE_ROWS); 

#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define MATRIX_PANEL        (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUM_LEDS            (MATRIX_WIDTH*MATRIX_HEIGHT)

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX, MATRIX_TILE_H, MATRIX_TILE_V> leds;

uint8_t angle = 0;
int inByte = 0;

void setup()
{
  Serial.begin(57600);
  
  
  FastLED.addLeds<CHIPSET, DATA_PIN,  COLOR_ORDER>(leds[0],leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(2);
  FastLED.clear(true);
 

  

//  // Japanese Flag
//  leds.DrawFilledRectangle(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
//  uint16_t r = min((leds.Width() - 1) / 2, (leds.Height() - 1) / 2) - 1;
//  leds.DrawFilledCircle((leds.Width() - 1) / 2, (leds.Height() - 1) / 2, r, CRGB(255, 0, 0));
//  FastLED.show();
//  delay(5000);


}


void loop()
{
  PurrLights();
  FastLED.show();
  
}

void PurrLights(){
  
  while(Serial.available() > 0){
    inByte = Serial.read();
    float radius = (float(inByte)/255.0)*14.0;
    LightAreaCircle2(radius);
  }
}

void LightAreaCircle2(float radius){
  FastLED.clear();
  leds.DrawFilledCircle((leds.Width() - 1) / 2, (leds.Height() - 1) / 2, radius, CRGB(255, 255,255));
}

void LightAreaCircle(float input){
  int w = MATRIX_WIDTH;
  int h = MATRIX_HEIGHT;
  float radiusOffset = 7.5;
  float radius = input;
  for(int x=0; x<w; x++){
    for(int y=0; y<h; y++){
      int pos = x *w + y;
      float xf = (float)x;
      float yf = (float)y;
      float dist = sqrt( ( xf-radiusOffset)*( xf-radiusOffset) + (yf-radiusOffset)*(yf-radiusOffset));

      if(dist < radius){
        float bright = 255.0 - (dist / max(radius,.001)) * 255.0; // diff shades of grey -> white
        leds(x,y) = CHSV(255,0,bright);
        
      } else {
        leds(x,y) = CHSV(0,0,0);
      }
    }
  }
}

