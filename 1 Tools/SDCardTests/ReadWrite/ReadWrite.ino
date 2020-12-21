/* TO DO:
 *  
 *  Change File from Text to Physical Data.
 *  Create Converter that reads current data file and converts it to the ideal file type
 *      - True Byte Equivalent
 *      - Commands
 *        - New Device
 *          -Device Port and Length
 *        - Update Device
 *          -Device RGB Colors
 *          -Make sure the device exists first
 *        - New Frame
 *        - 
 *  
*/
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>

#define PIN       3 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 9 // Popular NeoPixel ring size
#define MAXPIXELS 30
#define PORTS     5

CRGB Device[2][16];

int NumPixels[2] = {9, 16};

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

File myFile;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// Teensy audio board: pin 10
// Teensy 3.5 & 3.6 & 4.1 on-board: BUILTIN_SDCARD
// Wiz820+SD board: pin 4
// Teensy 2.0: pin 0
// Teensy++ 2.0: pin 20
const int chipSelect = BUILTIN_SDCARD;
const int PinOffSet = 24;

byte Red;
byte Green;
byte Blue;

byte Lines;

void setup(){
   // https://github.com/FastLED/FastLED/wiki/Parallel-Output
   FastLED.addLeds<NEOPIXEL, 2>(Device[0], 9);
   FastLED.addLeds<NEOPIXEL, 3>(Device[1], 16);
   

 // Open serial communications and wait for port to open:
 Serial.begin(9600);

  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
}
void loop(){
	// re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    // read from the file until there's nothing else in it:
    Lines = readNextFileByte(myFile);
    for(int frames=0; frames < Lines; frames++){
      for(int c=0; c < 2; c++){  
        for(int i=0; i < NumPixels[c]; i++) { // For each pixel...
          Red = readNextFileByte(myFile);
          Green = readNextFileByte(myFile);
          Blue = readNextFileByte(myFile);

          Device[c][i] = CRGB(-Red+255, -Green+255, -Blue+255);
        }
      }  
      FastLED.show();
      delay(DELAYVAL); // Pause before next pass through loop
     }
    // close the file:
    myFile.close();
  } 
  else {
   // // if the file didn't open, print an error:
   Serial.println("error opening test.txt");
  }
}

byte readNextFileByte(File FileOpen){
  char CharRead = "";
  String CollectedChars = "";
  for(int i=0; i<4; i++){
    CharRead = FileOpen.read();
    //Serial.println(CharRead);
    
    if(CharRead == ',' || CharRead == '\n'){
      byte a = ((byte) CollectedChars.toInt());
      //Serial.print("Byte Val: ");
     // Serial.println(a);
      return a;
    }
    else{
      CollectedChars += CharRead;
      //Serial.print("CharRead Val: ");
      //Serial.println(CharRead);
      //Serial.println((byte) CharRead);
      //Serial.println("-START-");
      
      //Serial.println("-END-");
    }
  }
}
