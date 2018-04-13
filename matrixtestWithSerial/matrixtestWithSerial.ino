// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6
#define BREAK_CHAR 10
#define BUFFER_SIZE 16
#define UNUSED -1
#define LED_OUT 13
#define OK_MSG "OK"
#define BAUD_RATE 57600

void LightArea(int[],int, bool);

// SERIAL
int inByte = 0;                 // incoming serial byte
int ptr = 0;                    // array pointer 
int frameBuffer[BUFFER_SIZE];   // buffer for characters

// STATES
bool isPurring = true;
bool isTalking = false;

// FORCE SENSOR (PETTING)
int pressurePin = A0;
int force;

// MATRIX
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
 
int x    = matrix.width();
int pass = 0;
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };


void setup() {
  Serial.begin(BAUD_RATE);
//  Serial.println("hello");
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(3);
  matrix.setTextColor(colors[0]);  
  initializeBuffer();
}

void loop() {
  if(isPurring){
    // TODO send a start signal to OF or there is no input to PurrLights()
    PurrLights();
  }          
}



void PurrLights(){
   while (Serial.available() > 0) { 
      inByte = Serial.read(); 
//      float radius = map(inByte,0,255,0,6);
      float radius = (float(inByte)/255.0)*6.0;
      LightAreaCircle(radius); 
      // Maybe ack here tbd
   } 
}

void LightAreaCircle(float input){
//  float radius = sin(millis()/10000.0) * 3 + 3;
  float radius = input;
   for(int i=0; i < 8; i++){
     for(int j=0; j < 8; j++){
        int pos = i * 8 + j;
        float iif = (float)i;
        float jf = (float)j;
        
        float dist = sqrt( ( iif-3.5)*( iif-3.5) + (jf-3.5)*(jf-3.5));
        if (dist < radius){
          
          float brigt = 255 - (dist / max(radius,.001)) * 255; // diff shades of grey -> white
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


/*
 * Return the ascii representation of the bytes sent
 * TODO a better way to do this using char[] and not String?
 */
String calcChunk(){
  String tmp; 
  for(int i=0; i<BUFFER_SIZE; i++){
    if(frameBuffer[i] != UNUSED){
      tmp+=char(frameBuffer[i]);
    }
  }
  return tmp;
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

//void Demand(String demand, int _delay){
//  matrix.fillScreen(0);
//  matrix.setCursor(x, 0);
//  matrix.print(F("PET ME."));
//  if(--x < -36) {
//    x = matrix.width();
//  }
//  matrix.show();
//  delay(_delay);
//}

//  delay(1); //doesn't seem necessary
//  Serial.write(OK_MSG);
//  force = analogRead(pressurePin);
//  Serial.println(force);

//  if(isTalking){
//    // TODO blip or bleep? 
//    // OK this whole thing doesn't work, it freezes in "PET ME"
//    // if it goes to harder.
//    // i wonder a better way to do this? like -- a little separate screen?
//    // a better program setup? the matrix for color patterns only? 
//    if(force < 50){
//      Serial.println("PET ME");
//      Demand("PET ME.", 100);
//    } else if(force > 50 && force < 100){
//      Serial.println("HARDER");
//      Demand("HARDER", 100);
//    } 
//  }
