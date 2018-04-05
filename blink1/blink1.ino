
#define CLK_OUT_PIN 13
#define CLK_ANA_IN A0

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK_OUT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t potValue = analogRead(CLK_ANA_IN);
  uint16_t potReading = map(potValue, 0,1023, 100,1000);
  digitalWrite(CLK_OUT_PIN, LOW);
  delay(potReading);
  digitalWrite(CLK_OUT_PIN, HIGH);
  delay(potReading);
}
