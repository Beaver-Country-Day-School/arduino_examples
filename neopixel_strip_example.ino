/*
 * This file contains an example of code that controls a Neopixel LED strip.
 * It runs through a sequence of actions:
 *  1. Turn the first 20 LEDS on, one at a time, in green. 
 *  2. Turn the first 20 LEDS on all at once, in red.
 *  3. Turn all the LEDS off.
 * 
 * Before running this code, you must install the "Adafruit NeoPixel" library:
 *  1. Open the Library Manager from the left sidebar, and search for "Adafruit Neopixel"
 *  2. Select "Adafruit NeoPixel" - it should be the first result.
 *     2a. Note you DON'T want "Adafruit DMA neopixel library" or "Adafruit NeoMatrix", or 
 *         any other similarly named library. Make sure you get the one named "Adafruit Neopixel".
 *  More in-depth instructions for library installation: 
 *  https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation
 *
 *  Tutorial on the NeoPixel library:
 *  https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
 * 
 *  Exhaustive documentation of the NeoPixel library:
 *  https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html
 *
*/

#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL  10   // Arduino pin that connects to NeoPixel
#define NUM_PIXELS     20  // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
    NeoPixel.begin(); // Initialize the neopixel strip - this is required
}

void loop() {
  NeoPixel.clear(); // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

  // turn pixels to green one by one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) { // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0)); // it only takes effect if pixels.show() is called
    NeoPixel.show();   // send the updated pixel colors to the NeoPixel hardware.
    delay(200); // pause between each pixel
  }
  delay(2000);

  // turn off all pixels for two seconds
  NeoPixel.clear();
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(2000);     // off time

  // turn on all pixels to red at the same time for two seconds
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) { // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0)); // it only takes effect if pixels.show() is called
  }
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(2000);     // on time

  // turn off all pixels for one seconds
  NeoPixel.clear();
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(2000);     // off time  
}
