// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

void LightArea(int[],int, bool);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

// hardcoded things for now.
const int center[] = {27,28,35,36};
int centerSize = 4;
const int r1[] = {18,19,20,21,29,37,45,44,43,42,34,26};
int r1Size = 12;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(3);
  matrix.setTextColor(colors[0]);  
}

void loop() {
//  LightArea(center, centerSize, true);
  LightAreaCircle();
  //delay(1);
}


void LightAreaCircle(){
  float radius = sin(millis()/1000.0) * 3 + 3;
   for(int i=0; i < 8; i++){
     for(int j=0; j < 8; j++){
        int pos = i * 8 + j;
        float iif = (float)i;
        float jf = (float)j;
        
        float dist = sqrt( ( iif-3.5)*( iif-3.5) + (jf-3.5)*(jf-3.5));
        if (dist < radius){
          float brigt = 255 - (dist / radius) * 255;
          matrix.setPixelColor(pos, brigt,brigt,brigt); 
        } else {
           matrix.setPixelColor(pos, 0,0,0); 
        }
     }
   }
  matrix.show();
}

void LightAreaRandom(){
  for(int i=0; i < 64; i++){
      matrix.setPixelColor(i, random(255), random(255), random(255)); 
      matrix.show();
      delay(10);
   }
  
}


void LightArea(const int Area[],int sizeArr, bool isOn){
   for(int i=0; i < sizeArr; i++){
    int c = Area[i];
//    Serial.println("cell number:");
//    Serial.println(c);
    if(isOn){
      matrix.setPixelColor(c, 255, 255, 255);  
    } else {
      matrix.setPixelColor(c, 0, 0, 0);  
    }
    
  }  
  matrix.show();
}
