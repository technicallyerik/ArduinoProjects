#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 1
#define PIXELS 19

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(128);
  strip.show();
}

void loop() {
  rainbowCycle(120);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, a, b;
  uint16_t half = PIXELS / 2;

  for(i = 0; i < 256; i = i + 5) {
    strip.setPixelColor(half, Wheel(i));
    for(a = 0; a < half ; a++) {
      for(b = 0; b < half; b++) {
        if(a == b) {
          strip.setPixelColor(half - 1 - b, Wheel(i));
          strip.setPixelColor(half + 1 + b, Wheel(i));
        } else {
          strip.setPixelColor(half - 1 - b, 0);
          strip.setPixelColor(half + 1 + b, 0); 
        } 
      }
      strip.show();
      delay(wait);
    }
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
