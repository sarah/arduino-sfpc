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

#define MATRIX_TYPE        (MTX_MATRIX_TOP | MTX_MATRIX_LEFT | MTX_MATRIX_ROWS | MTX_MATRIX_ZIGZAG | MTX_TILE_TOP | MTX_TILE_LEFT | MTX_TILE_ROWS); 

#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define MATRIX_PANEL        (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUM_LEDS            (MATRIX_WIDTH*MATRIX_HEIGHT)

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX, MATRIX_TILE_H, MATRIX_TILE_V> leds;

uint8_t angle = 0;

void setup()
{
  Serial.begin(57600);
  Serial.println("MATRIX_WIDTH");
  Serial.println(MATRIX_WIDTH);
  Serial.println("MATRIX_HEIGHT");
  Serial.println(MATRIX_HEIGHT);
  Serial.println("MATRIX_SIZE");
  Serial.println(MATRIX_SIZE);
  Serial.println("MATRIX_PANEL");
  Serial.println(MATRIX_PANEL);
  Serial.println("MATRIX_TILE_H");
  Serial.println(MATRIX_TILE_H);
  Serial.println("MATRIX_TILE_V");
  Serial.println(MATRIX_TILE_V);
  Serial.println("NUM_LEDS");
  Serial.println(NUM_LEDS);
  
  FastLED.addLeds<CHIPSET, DATA_PIN,  COLOR_ORDER>(leds[0],leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(2);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Lime);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.clear(true);

  // Scottish Flag
  leds.DrawFilledRectangle(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(0, 0, 255));
  leds.DrawRectangle(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
  leds.DrawLine(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
  leds.DrawLine(0, 1, leds.Width() - 1, leds.Height() - 2, CRGB(255, 255, 255));
  leds.DrawLine(0, leds.Height() - 1, leds.Width() - 1, 0, CRGB(255, 255, 255));
  leds.DrawLine(0, leds.Height() - 2, leds.Width() - 1, 1, CRGB(255, 255, 255));
  FastLED.show();
  delay(5000);

  // Japanese Flag
  leds.DrawFilledRectangle(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
  uint16_t r = min((leds.Width() - 1) / 2, (leds.Height() - 1) / 2) - 1;
  leds.DrawFilledCircle((leds.Width() - 1) / 2, (leds.Height() - 1) / 2, r, CRGB(255, 0, 0));
  FastLED.show();
  delay(5000);

  // Norwegian Flag
  int16_t x = (leds.Width() / 4);
  int16_t y = (leds.Height() / 2) - 2;
  leds.DrawFilledRectangle(0, 0, x, y, CRGB(255, 255, 255));
  leds.DrawFilledRectangle(0, 0, x - 1, y - 1, CRGB(255, 0, 0));
  leds.DrawFilledRectangle(x + 3, 0, leds.Width() - 1, y, CRGB(255, 255, 255));
  leds.DrawFilledRectangle(x + 4, 0, leds.Width() - 1, y - 1, CRGB(255, 0, 0));
  leds.DrawFilledRectangle(0, y + 3, x, leds.Height() - 1, CRGB(255, 255, 255));
  leds.DrawFilledRectangle(0, y + 4, x - 1, leds.Height() - 1, CRGB(255, 0, 0));
  leds.DrawFilledRectangle(x + 3, y + 3, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
  leds.DrawFilledRectangle(x + 4, y + 4, leds.Width() - 1, leds.Height() - 1, CRGB(255, 0, 0));
  leds.DrawLine(0, y + 1, leds.Width() - 1, y + 1, CRGB(0, 0, 255));
  leds.DrawLine(0, y + 2, leds.Width() - 1, y + 2, CRGB(0, 0, 255));
  leds.DrawLine(x + 1, 0, x + 1, leds.Height() - 1, CRGB(0, 0, 255));
  leds.DrawLine(x + 2, 0, x + 2, leds.Height() - 1, CRGB(0, 0, 255));
  FastLED.show();
  delay(5000);
  leds.ShiftLeft();
}


void loop()
{
  uint8_t h = sin8(angle);
  leds.ShiftLeft();
  for (int16_t y=leds.Height()-1; y>=0; --y)
  {
    leds(leds.Width()-1, y) = CHSV(h, 255, 255);
    h += 32;
  }
  angle += 4;
  FastLED.show();
  delay(20);
}
