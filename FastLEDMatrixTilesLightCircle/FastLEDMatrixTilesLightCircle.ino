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
#define MATRIX_TYPE         (MTX_MATRIX_TOP | MTX_MATRIX_LEFT | MTX_MATRIX_ROWS | MTX_MATRIX_ZIGZAG | MTX_TILE_TOP | MTX_TILE_LEFT | MTX_TILE_ROWS); 
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define MATRIX_PANEL        (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUM_LEDS            (MATRIX_WIDTH*MATRIX_HEIGHT)



#define WAITING 0
#define SOFT_PURR 100
#define MORE_PURR 200
#define NO_STOP 300
#define RETRACT 400

bool stateWaiting =  true;
bool stateSoftPurr = false;
bool stateMorePurr = false;
bool stateNoStop = false;
bool stateRetract = false;

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX, MATRIX_TILE_H, MATRIX_TILE_V> leds;


const int petPressurePin = A0;
const int buttonPin = 2;
const int timeToWindDown = 10000;
unsigned long currentMillis = 0;
unsigned long lastPetMillis = 0;   // will store last time the LED was updated

int inByte = 0;
int force;
int buttonState = 0; 


#define LOGGING false
void Log(String data){
  if(LOGGING){
    Serial.println(data);
  }
}

void loop()
{
  currentMillis = millis();
  readPetSensor();
  manageStates();
}

void manageStates(){
  if(stateWaiting){
    Log("Waiting");
    showWaitingState();
  } 
  
  if(stateSoftPurr){
    Log("Softpurr");
    Serial.print(SOFT_PURR);
  } else if(stateMorePurr){
    Log("Sending More purr");
    Serial.print(MORE_PURR);
  }
  
  if(stateSoftPurr || stateMorePurr){
    PurrLights();
  }
}

void readPetSensor(){
  Log((String)force);
 
  force = analogRead(petPressurePin);
  if((force > 50 && force < 100) && !stateMorePurr){
    Log("MOVING TO SOFT PURR");
    stateWaiting = false;
    stateSoftPurr = true;
  }
  
  if(force > 150){
    Log("Moving to moar purr");
    stateSoftPurr = false;
    stateMorePurr = true;
    lastPetMillis = currentMillis;
    // log current time, so this is "last time we've been above 150"
  } else {
      if(currentMillis - lastPetMillis >= timeToWindDown){
        stateMorePurr = false;
        Serial.print(NO_STOP);  
        stateWaiting = true;  
        // TODO figure out the time slow down thing i'm too tired to think right now



          
  }
    
    // if not, how much time have we been not petting?
    // if time not petting > interval; switch to waiting state (possibly squeak)  
    // 1
  }
}

void showWaitingState(){
  // TODO get the circle where I want it.
    FastLED.clear();
    leds.DrawFilledCircle((leds.Width() - 1) / 4, (leds.Height() - 1) / 4, 1, CRGB(255, 0, 0));
    FastLED.show();
}

void PurrLights(){
  while(Serial.available() > 0){
    inByte = Serial.read();
    Serial.flush();
    if(inByte < 251){
      float radius = (float(inByte)/255.0)*10.0;
      LightAreaCircle2(radius);  
    } else {
      ShowTestLight(0,0);
    }
    FastLED.show();
  }
}

void ShowTestLight(int x,int y){
  Log("SHOW TEST LIGHT");
  FastLED.clear();
  leds(x,y) = CRGB(0,255,0);
  FastLED.show();
}
void LightAreaCircle2(float radius){
  FastLED.clear();
  // TODO how to do the brightness here
  int x = (leds.Width() - 1)/2;
  int y = (leds.Height() - 1)/2;  
  leds.DrawFilledCircle(x,y, radius, CRGB(255, 255,(255-radius)));
  // just playing with color
//  leds.DrawFilledCircle(x,y, max(radius-2,1), CHSV(255, 0,50));
}

void LightAreaCircle(float input){
  FastLED.clear();
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


void setup()
{
  Serial.begin(57600);
  Log("Hello");
  FastLED.addLeds<CHIPSET, DATA_PIN,  COLOR_ORDER>(leds[0],leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(20);
  FastLED.clear(true);
  pinMode(buttonPin, INPUT);
}

//  // Japanese Flag
//  leds.DrawFilledRectangle(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
//  uint16_t r = min((leds.Width() - 1) / 2, (leds.Height() - 1) / 2) - 1;
//  leds.DrawFilledCircle((leds.Width() - 1) / 2, (leds.Height() - 1) / 2, r, CRGB(255, 0, 0));
//  FastLED.show();
//  delay(5000);

