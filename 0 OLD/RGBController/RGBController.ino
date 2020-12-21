#include <Adafruit_NeoPixel.h>

#define STARTNUMPIXELS 9 // Popular NeoPixel ring size
#define PORTS 14

Adafruit_NeoPixel pixels[14];

//Global Variables
byte colors[255]; //Maximum of 255 pixels per channel 
byte PixelsSelected[1]; // Needs to be array but only uses 1 byte
byte PixelsConfig[2]; //Startup Configuration
bool SetupDone = false;

void setup() {
  for(int c=2; c < PORTS; c++){ // INITIALIZE ALL OBJECTS
    pixels[c] = Adafruit_NeoPixel(STARTNUMPIXELS, c, NEO_GRB + NEO_KHZ800);
    pixels[c].begin(); // INITIALIZE NeoPixel strip object
  }
  
  Serial.begin(0);
  //Serial.setTimeout(50);
  
  while(!SetupDone){ // Wait for all Objects to be fully configured
    if(readNoOfBytes(PixelsConfig, 2)){
      Serial.println(PixelsConfig[0]);
      Serial.println(PixelsConfig[1]);
      if(PixelsConfig[0] != 255){
        //pixels[PixelsConfig[0]].updateLength((int) PixelsConfig[1]);
      }
      else{ // Setup Exit Command Given.
        SetupDone = true;
      }
    }
  }
}

void loop() {
    if(readNoOfBytes(PixelsSelected, 1)){
      if(readNoOfBytes(colors, pixels[PixelsSelected[0]].numPixels() * 3)){
        for(int c=0; c < (pixels[PixelsSelected[0]].numPixels()); c++){
          for(int i=0; i < 3; i++){
           pixels[PixelsSelected[0]].setPixelColor(c, pixels[PixelsSelected[0]].Color((int) colors[(c*3)], (int) colors[(c*3)+1], (int) colors[(c*3)+2]));
          }
        }
        pixels[PixelsSelected[0]].show();
      }
      delay(100);
    }
}

bool readNoOfBytes(byte Buffer[], int BytesToRead){
  if (Serial.available()) {
    for(int i=0; i < BytesToRead; i++){
      Buffer[i] = Serial.read();  // will not be -1
    }
    return true;
  }
  else{
    return false;
  }
}

  
