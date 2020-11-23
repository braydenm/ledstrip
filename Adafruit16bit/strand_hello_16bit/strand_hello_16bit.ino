#include <Adafruit_DotStar_16bit.h>
#include <SPI.h>

#define NUMPIXELS 72*5 // Number of LEDs in strip

//Make sure to connect led strip to the correct (default) SPI pins. 
// For  ESP8266
//  Clock: HSCLK = 14 = GPIO 14 = D5 (Yellow)
//  Data: HMOSI = 13 = GPIO13 = D7 (Green)
// For ESP32 use:
//  Clock: SCLK = 18=  P18 = VSP|SCK
//  Data: MOSI = GPIO23 = P23 = 23 

// Here's how to override the default pins:
//#define CLOCKPIN   18
//#define DATAPIN    23

uint16_t lastcolorred = 0xFF;
uint16_t lastcolorgreen = 0x00;
uint16_t lastcolorblue = 0xFF;
uint32_t lastcolor = (lastcolorred << 16) | (lastcolorgreen << 8) | (lastcolorblue);

Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_RGB);
void setup() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

void loop() {
  strip.setPixelColor(0, 0x000000FF0000); //First pixel is red
  strip.setPixelColor(1, 0x00000000FF00); //Second pixel is green
  strip.setPixelColor(2, 0x0000000000FF); //Third pixel is blue
  strip.setPixelColor(3, 0xFF0000); //Fourth pixel is red
  strip.setPixelColor(4, 0x00FF00); //Fifth pixel is green
  strip.setPixelColor(5, 0x0000FF); //Sixth pixel is blue
  strip.setPixelColor(6, lastcolor); //Seventh pixel is made by bit shifting and |
  strip.show();                     // Refresh strip
  delay(10);                        // Pause 20 milliseconds (~50 FPS)
}
