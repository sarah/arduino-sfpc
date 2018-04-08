/*
  Serial Example 2

  Sends and receives serial data
*/

int inByte = 0;         // incoming serial byte

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(57600);
  Serial.println("hello");
}

// the loop function runs over and over again forever

 void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) { 
                /*
                 * 
                   reads each byte and returns the ascii representation of that byte
                   by default it returns the representation in decimal (DEC)
                   but you can specify other units (HEX or BIN) which will return the HEX or BIN representation   
                   So if you send the string "cat", you would get three characters followed by a line feed
                   in DECIMAL this program would run: (c == 99, a == 97, t == 116)

                    I received DEC: 99
                    I received DEC: 97
                    I received DEC: 116
                    I received DEC: 10                 
                */
                
                inByte = Serial.read(); 
                Serial.print("I received DEC: ");
                Serial.println(inByte);  
        }
}
 

