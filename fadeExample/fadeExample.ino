#define LED_OUT 9
bool fadingUp = true;

void setup() {
  Serial.begin(9600);
  pinMode(LED_OUT, OUTPUT);
}

void loop() {
  
  int i = 0;
  Serial.print("starting\n");

  // fades up
  while(i < 1024){
    Serial.print(i);
    Serial.print("\n");
    
    analogWrite(LED_OUT, i);
    delay(10);
    i++;  
  }
  Serial.print("descending\n");
  
  while(i > 0){
    analogWrite(LED_OUT, i);
    delay(10);
    i--;  
  }
}
