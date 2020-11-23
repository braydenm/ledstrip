#include <SPI.h>
#include <Adafruit_DotStar_16bit.h>

#define NUMPIXELS 5*72 //Length of your strip
#define DELAY 1
#define SNAKELENGTH 7

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
Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

void bounceBetween(uint64_t color, uint16_t start, uint16_t finish, uint16_t len){

  int path_length = finish-start ;
  
  // Get light snake moving forward down the line.
  for (int i=0 ; i < path_length ; i++){
    // Populate the snake
    for (int j=0 ; j < len ; j++){
      if ((j+i+start) <= finish){
        strip.setPixelColor(i+j+start, color) ;
        strip.show() ;
      }
    }
    // Write the end of the snake to be "off"
    if ( (i+start) <= (finish-len) ){
      strip.setPixelColor(i+start, 0) ;
      delay(DELAY) ;
    }
  }

  color = randColor() ;
  // Get the light snake moving backwards.
  for (int i=0 ; (-1)*i < path_length ; i--){
    // Populate the snake
    for (int j=0 ; (-1)*j < len ; j--){
      if ((i+j+finish) >= start){
        strip.setPixelColor(i+j+finish, color) ;
        strip.show() ;  
      }
    }
    // Write the end of the snake to be "off"
    if ( (i+finish) >= (len+start) ){
      strip.setPixelColor(i+finish, 0) ;
      delay(DELAY) ;
    }
  }
}

uint32_t randColor(){
  uint8_t red = random(0,255) ;
  uint8_t blue = random(0,255) ;
  uint8_t green = random(0,255) ;

  uint64_t color = 0x000000000000 ; //GRB

  color = color | (green << 32) ;
  color = color | (red << 16) ;
  color = color | blue ;

  return color ;
}

void setup() {
  strip.begin() ;
  strip.show() ;
}

void loop() {
  uint64_t color = randColor() ;
  bounceBetween(color, 0, NUMPIXELS, SNAKELENGTH ) ;
}
//>
