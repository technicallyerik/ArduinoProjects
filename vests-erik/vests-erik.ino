// Board:  Adafruid Gemma 8MHz
// Programmer: USBTinyISP

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(128);
  strip.show(); 
}

void loop() {
  rainbowfall(10);
  sparkle(10);
}

void rainbowfall(uint8_t wait) {

  uint16_t i, j;
  uint16_t pixels = strip.numPixels() / 4;

  for(j = 0; j < 256; j++) {
    for(i = 0; i < pixels ; i++) {
      // Strip 1
      strip.setPixelColor(15 + i, Wheel((int)(pow(i,2)+j) & 255));
      // Strip 2
      strip.setPixelColor(14 - i, Wheel((int)(pow(i,2)+j) & 255));
      // Strip 3
      strip.setPixelColor(45 + i, Wheel((int)(pow(i,2)+j) & 255));
      // Strip 4
      strip.setPixelColor(44 - i, Wheel((int)(pow(i,2)+j) & 255));
    }
    strip.show();
    delay(wait);
  }
  
}

void sparkle(uint8_t wait) {

  uint16_t i, j, c, o;

  for(j = 0; j < 20; j++) {
    
    for(i = 0; i < strip.numPixels(); i++) {
      o = random(0, 2);
      if(o == 1) {
        c = random(0, 255);
        strip.setPixelColor(i, Wheel(c & 255));
      } else {
        strip.setPixelColor(i, 0);
      }
    }

    strip.show();
    delay(wait);
  }
  
}

void black(uint8_t wait) {
  uint16_t i, j, c;
  for(i=0; i < (strip.numPixels()); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
  delay(wait);
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
