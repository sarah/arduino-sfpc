#define BTN_PIN_TWOS 2
#define BTN_PIN_ZEROS 3

#define LED_PIN_TWOS 8
#define LED_PIN_ZEROS 9

bool twosPressed = false;
bool zerosPressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN_TWOS, INPUT);
  pinMode(BTN_PIN_ZEROS, INPUT);
  
  pinMode(LED_PIN_TWOS, OUTPUT);
  pinMode(LED_PIN_ZEROS, OUTPUT);
}

void loop() { 
  zerosPressed = digitalRead(BTN_PIN_ZEROS);
  twosPressed = digitalRead(BTN_PIN_TWOS);
  
  if(zerosPressed && !twosPressed){
    digitalWrite(LED_PIN_ZEROS, HIGH);
  } else {
    digitalWrite(LED_PIN_ZEROS, LOW);
  }

  if(twosPressed && !zerosPressed){
    digitalWrite(LED_PIN_TWOS, HIGH);
  } else{
    digitalWrite(LED_PIN_TWOS, LOW);
  }

  if(zerosPressed && twosPressed){
    digitalWrite(LED_PIN_TWOS, HIGH);
    digitalWrite(LED_PIN_ZEROS, HIGH);
  } else {
    digitalWrite(LED_PIN_TWOS, LOW);
    digitalWrite(LED_PIN_ZEROS, LOW);
  }
  
}
