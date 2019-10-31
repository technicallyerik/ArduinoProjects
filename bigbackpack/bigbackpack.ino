#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(71, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(32);
  strip.show();
}

void loop() {
  rainbowCycle(40);
}

void rainbowCycle(uint8_t wait) {
  uint16_t a, b, c, i, j;
  uint16_t stripPixels = 15;

  for(j = 0; j < 256; j++) {
    for(i = 0; i < stripPixels; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / stripPixels) + j) & 255));
      strip.setPixelColor((stripPixels * 2) - 1 - i, Wheel(((i * 256 / stripPixels) + j) & 255));

      if(i == 0) {
        for(a = 30; a < 54; a++) {
          strip.setPixelColor(a, Wheel(((i * 256 / stripPixels) + j) & 255));
        }
      }

      if(i == 5) {
        for(b = 54; b < 70; b++) {
          strip.setPixelColor(b, Wheel(((i * 256 / stripPixels) + j) & 255));
        }
      }

      if(i == 10) {
        for(c = 70; c < 71; c++) {
          strip.setPixelColor(c, Wheel(((i * 256 / stripPixels) + j) & 255));
        }
      }
      
      //strip.setPixelColor(i + (pixels * 2), Wheel((int)(pow(i,2)+j) & 255));
      //strip.setPixelColor(strip.numPixels() - 1 - i, Wheel((int)(pow(i,2)+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
