#include <SPI.h>
#include <Adafruit_DotStar_16bit.h>

#define NUMPIXELS 5*72 //Length of your strip
//#define DELAY 20
#define SNAKELENGTH 7
#define START 0

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

// Create the strip
Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_RGB);

void bounceBetween(uint64_t color, uint64_t color2){

  int path_length = NUMPIXELS-START ;
  
  // Get light snake moving forward down the line.
  for (int i=0 ; i < path_length ; i++){

    // Populate the snake
    for (int j=0 ; j < SNAKELENGTH ; j++){
      if ((j+i+START) <= NUMPIXELS){
        strip.setPixelColor(i+j+START, color) ;
      }
    }

    // Write the end of the snake to be "off"
    if ( (i+START) <= (NUMPIXELS-SNAKELENGTH) ){
      strip.setPixelColor(i+START, 0) ;
//      delay(DELAY) ;
    }
  strip.show();
  }

  // Get the light snake moving backwards.
  for (int i=0 ; (-1)*i < path_length ; i--){

    // Populate the snake
    for (int j=0 ; (-1)*j < SNAKELENGTH ; j--){
      if ((i+j+NUMPIXELS) >= START){
        strip.setPixelColor(i+j+NUMPIXELS, color2) ;
      }
    }

    // Write the end of the snake to be "off"
    if ( (i+NUMPIXELS) >= (SNAKELENGTH+START) ){
      strip.setPixelColor(i+NUMPIXELS, 0) ;
//      delay(DELAY) ;
    }
  strip.show();
  }
}

uint32_t randColor(){
  uint8_t red = random(0,255) ;
  uint8_t blue = random(0,255) ;
  uint8_t green = random(0,255) ;

  uint64_t color = 0x000000 ; //RGB

  color = color | (red << 16) ;
  color = color | (green << 8) ;
  color = color | blue ;

  return color ;
}

void setup() {
  strip.begin() ;
  strip.show() ;
}

void loop() {
  uint64_t color = randColor() ;
  uint64_t color2 = randColor() ;
  bounceBetween(color, color2) ;
}
//>
