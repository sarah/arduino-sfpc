
#include <stdlib.h>

#define BREAK_CHAR 10
#define BUFFER_SIZE 16
#define UNUSED -1
#define LED_OUT 13
#define OK_MSG "OK"
#define BAUD_RATE 57600

int inByte = 0;                 // incoming serial byte
int ptr = 0;                    // array pointer 
int frameBuffer[BUFFER_SIZE];   // buffer for characters


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("hello");
  pinMode(LED_OUT, OUTPUT);
  initializeBuffer();
}


/*
 * So if I want to send numbers between 0-255 from my openframeworks project
 * and those correspond to 
 * No. I have the FFT data. Confirm it corresponds to 0-255, or what it conforms to
 * I will want to receive that and understand "these 3 inBytes are one chunk of data that represent "2" "5" "5" (255)
 * Now use that data to light the lights then get the next chunk

 */

 void loop() {
        if (Serial.available() > 0) { 
                inByte = Serial.read(); 
                digitalWrite(LED_OUT, LOW);
                if(inByte != BREAK_CHAR){
                   frameBuffer[ptr] = inByte;
                   ptr++;
                } else {
                  // end of chunk
                  String chunk = calcChunk();
                  Serial.println("Chunk was:");
                  Serial.println(chunk);

                  // little visual test of "cat" or other data
                  if(chunk == "cat"){
                    digitalWrite(LED_OUT, HIGH);
                  } else{
                    Serial.println("turn off led?");
                    digitalWrite(LED_OUT, LOW);
                  }
                  
                  Serial.write(OK_MSG);
                  resetBuffer();
                  
                          
                }               
                // send an ack
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




