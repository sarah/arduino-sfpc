// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

const uint8_t center[] = {27,28,35,36};
const uint8_t ring1[] = {18,19,20,21,29,37,45,44,43,42,34,26};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(3);
  matrix.setTextColor(colors[0]);  
}

int x    = matrix.width();
int pass = 0;
int b = 0;

void loop() {
//    matrix.fillScreen(1);
//    matrix.setBrightness(3);
//    b++;
//    if(b > 30){
//      b-- ;
//    }
for(int i=0; i < sizeof(center); i++){
  matrix.setPixelColor(center[i], 255, 255, 255);
  matrix.show();
}
  
  delay(1000);
  // set pixel to off, delay(1000)
  for(int i=0; i < sizeof(center); i++){
  matrix.setPixelColor(center[i], 0, 0, 0);
  matrix.show();
}
//  matrix.setPixelColor(0, 0, 0, 0);
//  matrix.show();
  delay(1000);

    
//    for( int i = 0; i < sizeof(center); i++){
//      matrix.setPixelColor(center[i], 255,255,255); // white
//      matrix.show();
//    }

//    matrix.setPixelColor(0, 255,255,255); // white
//    matrix.show();
//    delay(2000);
//     matrix.setPixelColor(0, 0,0,0); // white
//     matrix.show();
//    for( int i = 0; i < sizeof(center); i++){
//      matrix.setPixelColor(center[i], 0);
//      matrix.show();
//    }
//    
//  matrix.fillScreen(0);
//  matrix.setCursor(x, 0);
//  matrix.print(F("PURR"));
//  if(--x < -36) {
//    x = matrix.width();
//    if(++pass >= 3) pass = 0;
//    matrix.setTextColor(colors[pass]);
//  }
//  matrix.show();
//  delay(100);
}
