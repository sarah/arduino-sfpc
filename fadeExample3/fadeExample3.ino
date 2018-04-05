#define LED_OUT 11
#define MAX_LIGHT 255
#define MIN_LIGHT 0

int brightness = 0;
int fadeAmt = 5;

void setup() {
  Serial.begin(9600);
  pinMode(LED_OUT, OUTPUT);
}

void loop() {
    analogWrite(LED_OUT, brightness);
    brightness = brightness + fadeAmt;

    if(brightness <= MIN_LIGHT || brightness >= MAX_LIGHT){
     fadeAmt = -fadeAmt;
    }
    Serial.print(brightness);
    Serial.print("\n");
    Serial.print(fadeAmt);
    Serial.print("\n");
    Serial.print("\n");
    
    delay(30);
}
