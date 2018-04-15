// this actually fucking works
// http://samsneatprojectblogcode.blogspot.com/2016/06/force-sensor-code-and-wiring.html
// i took some pictures of my LED setup on the breadboard. 
int pressurePin = A0;
int force;
int LEDpin = 12;
void setup() {
  Serial.begin(57600);
  Serial.println("hello");
//pinMode(LEDpin, OUTPUT);
}
void loop() {
  force = analogRead(pressurePin);
//  Serial.println(force);
  Serial.println(force);
if(force > 300)
{
//  Serial.println("Over 300");
//  digitalWrite(LEDpin, HIGH);
}
else
{
//  Serial.println("Under 300");
//  digitalWrite(LEDpin, LOW);
}
delay(100);
}


