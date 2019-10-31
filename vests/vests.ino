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
  chase(50);
  boop(250);
  black(100);
  boop(250);
  black(100);
  rise(100);
}

void chase(uint8_t wait) {
  uint16_t i, j, c;

  for(j=0; j<strip.numPixels(); j++) {

    // Clear individual pixels
    for(i=0; i < (strip.numPixels()); i++) {
      strip.setPixelColor(i, 0);
    }

    // Light individual pixel
    c = (int)(255 / strip.numPixels()) * j;
    if(j < 15) {  // Row one = 29 (bottom) to 15  (top)
      i = 29 - j;
    } else if(j < 30) { // Row two = 0 (bottom) to 14 (top)
      i = 29 - j;
    } else if(j < 45) { // Row three = 59 (bottom) to 45 (top)
      i = 59 - (j - 30);
    } else if(j < 60) { // Row four = 30 (bottom) to 44 (top)
      i = 45 - (j - 44);
    }
    strip.setPixelColor(i, Wheel(c & 255));

    // Set pixels
    strip.show();
    delay(wait);
  }
}

void boop(uint8_t wait) {
  uint16_t i, j, c;

  c = random(0, 255);
  for(i=0; i < (strip.numPixels()); i++) {
    strip.setPixelColor(i, Wheel(c & 255));
  }
  strip.show();
  delay(wait);
}

void rise(uint8_t wait) {
  uint16_t i, j, c;

  for(i=0; i < (strip.numPixels() / 4); i++) {

    for(j=0; j < (strip.numPixels()); j++) {
      strip.setPixelColor(j, 0);
    }
    
    c = (int)(255 / (strip.numPixels() / 4)) * i;
    strip.setPixelColor((29 - i), Wheel(c & 255));
    strip.setPixelColor(i, Wheel(c & 255));
    strip.setPixelColor(59 - i, Wheel(c & 255));
    strip.setPixelColor(30 + i, Wheel(c & 255));
    strip.show();
    delay(wait);
  }
  delay(wait);

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
