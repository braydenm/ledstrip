// the sensor communicates using SPI, so include the library:
#include <SPI.h>

//Make sure to connect led strip to the correct (default) SPI pins.

// For  ESP8266
//  Clock: HSCLK = 14 = GPIO 14 = D5 (Yellow)
//  Data: HMOSI = 13 = GPIO13 = D7 (Green)
// For ESP32 use:
//  Clock: SCLK = 18=  P18 = VSP|SCK
//  Data: MOSI = GPIO23 = P23 = 23 

#define NUMPIXELS 5*72 // 5m strip x 72 pixels/m

// Goal: Print the first 3 pixels of the strand as R, G, and Blue.

uint16_t red[NUMPIXELS] = {0};
uint16_t green[NUMPIXELS] = {0};
uint16_t blue[NUMPIXELS] = {0};

uint8_t up = {0x1};
uint8_t blueb = {0x1F};  //Default to 11111 for max
uint8_t greenb = {0x1F}; //Default to 11111 for max
uint8_t redb = {0x1F};   //Default to 11111 for max
uint16_t global = {0xFFFF};

void setup() {
  // start the SPI library:
  SPI.begin();

  //Set the first three pixels to be red, green, and blue respectively
  red[0] = 0xFFFF;
  green[1] = 0xFFFF;
  blue[2] = 0xFFFF;

  //Overwrite the 5-bit brightness values here if desired:
  blueb = 0b11000;
  greenb = 0b00000;
  redb = 0b00011;

  //Concatenate the  the frame start, and 5-bit brightness values for R/G/B
  global = (up << 15)| (redb << 10) | (greenb << 5) | blueb;
}

void loop() {
    write_strand();
    delay(1);
}

void write_strand() {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));

  // Start frame - 128bit of 0
  for (int i = 0; i < 8; i++) {SPI.transfer16(0);}
  
  // LEDs
  for (int i = 0; i < NUMPIXELS; i++) {
      
    //Send 16 bits represtening frame LEDframe start and global brighness
    SPI.transfer16(global);

    // 48 bits (LED frame RGB color data, 16bit x 3)
    SPI.transfer16(red[i]);
    SPI.transfer16(green[i]);
    SPI.transfer16(blue[i]);
  }
  // End Frame- write "1"s equal to at least how many pixels are in the string.
  for (int i = 0; i < NUMPIXELS/16 +1; i++) {SPI.transfer16(0xFFFF);}
  SPI.endTransaction();
}
