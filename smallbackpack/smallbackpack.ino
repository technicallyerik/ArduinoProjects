#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(48, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(64);
  strip.show();
}

void loop() {
  rainbowCycle(10);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  uint16_t pixels = strip.numPixels() / 4;

  for(j = 0; j < 256; j++) {
    for(i = 0; i < pixels ; i++) {
      // Wheel(((i * 256 / pixels) + j) & 255)
      strip.setPixelColor(i + (pixels * 0), Wheel((int)(pow(i,2)+j) & 255));
      strip.setPixelColor((strip.numPixels() / 2) - 1 - i, Wheel((int)(pow(i,2)+j) & 255));
      
      strip.setPixelColor(i + (pixels * 2), Wheel((int)(pow(i,2)+j) & 255));
      strip.setPixelColor(strip.numPixels() - 1 - i, Wheel((int)(pow(i,2)+j) & 255));
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
