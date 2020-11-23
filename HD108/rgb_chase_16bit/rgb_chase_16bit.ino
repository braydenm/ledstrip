// the sensor communicates using SPI, so include the library:
#include <SPI.h>

//Make sure to connect led strip to the correct (default) SPI pins.
// For  ESP8266
//  Clock: HSCLK = 14 = GPIO 14 = D5 (Yellow)
//  Data: HMOSI = 13 = GPIO13 = D7 (Green)
// For ESP32 use:
//  Clock: SCLK = 18=  P18 = VSP|SCK
//  Data: MOSI = GPIO23 = P23 = 23 

#define NUMPIXELS 5*72

//Store the RBG values at every location on the LED strip
uint16_t red[NUMPIXELS] = {0};
uint16_t green[NUMPIXELS] = {0};
uint16_t blue[NUMPIXELS] = {0};

//Define the LED Frame header and brightnesses
uint8_t up = {0x1};
uint8_t blueb = {0x1F};  //Default to 11111
uint8_t greenb = {0x1F}; //Default to 11111
uint8_t redb = {0x1F};   //Default to 11111
uint16_t global = {0xFFFF};

void setup() {
  // start the SPI library:
  SPI.begin();

  //Overwrite the 5-bit brightness values here if desired:
  blueb = 0b10000;
  greenb = 0b00000;
  redb = 0b00000;

  //Concatenate the  the frame start, and 5-bit brightness values for R/G/B
  global = (up << 15)| (redb << 10) | (greenb << 5) | blueb;
}

void loop() {
  // Create an animation with NUMPIXELS of frames
  for (int i = 0; i < NUMPIXELS; i++) {
    
    //Turn off all pixesl
    clear_strand();

    //Move the location of each of the colored pixels
    green[i] = 0xFFFF;
    blue[(2 * i) % (NUMPIXELS)] = 0xFFFF;
    red[(3 * i) % (NUMPIXELS)] = 0xFFFF;
    
    write_strand();

    //Add an impercepable delay after each frame to ensure slower chips don't lock up
    delay(0);
  }
}

void write_strand() {
    SPI.beginTransaction(SPISettings(1*1E6, MSBFIRST, SPI_MODE0));

  // Start frame - 128bits of 0
  for (int i = 0; i < 8; i++) {SPI.transfer16(0);}
  
  // LEDs
  for (int i = 0; i < NUMPIXELS; i++) {
 
    //Send 16 bits represtening frame LEDframe start and global brightness current gain adjustment data
    SPI.transfer16(global);

    // 48 bit LED frame RGB color data (16bit x 3)
    SPI.transfer16(red[i]);
    SPI.transfer16(green[i]);
    SPI.transfer16(blue[i]);
  }
  
  // End Frame- write "1"s equal to at least how many pixels are in the string.
  for (int i = 0; i < NUMPIXELS/16 +1; i++) {SPI.transfer16(0xFFFF);}

  SPI.endTransaction();
}
void clear_strand() {
    for (int i = 0; i < NUMPIXELS; i++) {
      red[i] = 0;
      green[i] = 0;
      blue[i] = 0;
    }
}
