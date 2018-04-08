/*
  Serial Example 2

  Sends and receives serial data
*/

#define BREAK_CHAR 10
#define BUFFER_SIZE 5
#define UNUSED -1

int inByte = 0;                                 // incoming serial byte
int frameBuffer[BUFFER_SIZE] {UNUSED,UNUSED,UNUSED,UNUSED,UNUSED};  // buffer for characters
int ptr = 0;                                     // array pointer? 

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(57600);
  Serial.println("hello");
}

/*
 * So if I want to send numbers between 0-255 from my openframeworks project
 * and those correspond to 
 * No. I have the FFT data. Confirm it corresponds to 0-255, or what it conforms to
 * I will want to receive that and understand "these 3 inBytes are one chunk of data that represent "2" "5" "5" (255)
 * Now use that data to light the lights then get the next chunk

 */

 void loop() {

        // send data only when you receive data:

        if (Serial.available() > 0) { 
                inByte = Serial.read(); 
               
                if(inByte != BREAK_CHAR){
                   frameBuffer[ptr] = inByte;
                   ptr++;
                } else {
                  Serial.println("end of chunk");
                  Serial.println("Chunk was:");
                  for(int i=0; i< BUFFER_SIZE; i++){
                    if(frameBuffer[i] != UNUSED){
                      Serial.println(frameBuffer[i]);  
                    }
                    frameBuffer[i] = -1;
                  }
                  ptr = 0; // reset ptr
                }
        }
}
 

