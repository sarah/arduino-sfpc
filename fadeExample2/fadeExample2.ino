#define POT 0
#define LED_OUT 10

// attaches a potentiometer to an LED
void setup() {
  pinMode(POT, INPUT);
  pinMode(LED_OUT, OUTPUT);
}

void loop() {
  int val = analogRead(POT);
  analogWrite(LED_OUT, val);
}
