#include "Arduino.h"
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

#include "global.h"
#include "functions.h"

CRGB Device[MAXPORTS][MAXPIXELS];

byte deviceNumPixels[MAXPORTS];

File frames;
char selectedFile[255];
char workingFile[255];

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

unsigned int delayval = 1000; // Time (in milliseconds) to pause between pixels
unsigned int errorDelayVal = 1000; // Time to pause between alerting errors for opening files

byte red = 0;
byte green = 0;
byte blue = 0;

byte hue = 0;
byte sat = 0;
byte value = 0;

byte commandSelect = 255;
byte port = 255;
int pixelsCount = 0;

unsigned long frameStartTime = 0;
unsigned long currentTime = 0;

char serialCommand = 'A';
int lengthToRead = 0;

bool forceNewFile = false;

void setup(){

  //Set Default file
  charArrayWriter(selectedFile, (char*) "frames4.txt");
  
  for(int i=0; i < MAXPORTS; i++){
    deviceNumPixels[i] = 0; // Initalizes the Array for Error Checking later
  }
 // Open serial communications and wait for port to open:
 Serial.begin(9600); // Does not need to set a speed but is written for conventions
 Serial.setTimeout(0); // Makes it not pause after reading in the Serial Commands

  delay(10); // Used In Example before SD card. I assume to allow SD to initalize??

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }

  frameStartTime = millis(); // Start the First Frame time
}

void loop(){
	// re-open the file for reading:
  frames = SD.open(selectedFile);
  if(frames){
    // read from the file until there's nothing else in it:
    while(frames.available()){
      switch (frames.read()){ // Read Command
        
        // RGB Color Sending
        case 0:{
          port = frames.read();
          pixelsCount = deviceNumPixels[port];
          if(pixelsCount == 0){ // No device should have 0 pixels
            Serial.print("Device: ");
            Serial.print(port);
            Serial.println(" not setup!");
          }
          else { // Update Pixels
            for(int i=0; i < pixelsCount; i++){
              red = frames.read(); // Read Red Val
              green = frames.read(); // Read Green Val
              blue = frames.read();  // Read Blue Val
              Device[port][i] = CRGB(-red+255, -green+255, -blue+255); // Update RAM for Pixels Info
            }
          }
          break;
        }
  
        // HSV Color Sending
        case 1:{
          port = frames.read();
          pixelsCount = deviceNumPixels[port];
          if(pixelsCount == 0){ // No device should have 0 pixels
            Serial.print("Device: ");
            Serial.print(port);
            Serial.println(" not setup!");
          }
          else { // Update Pixels
            for(int i=0; i < pixelsCount; i++){
              hue = frames.read(); // Read Hue Val
              sat = frames.read(); // Read Saturation Val
              value = frames.read();  // Read Value Val
              HSVtoRGB(hue, sat, value);

              Device[port][i] = CRGB(-red+255, -green+255, -blue+255); // Update RAM for Pixels Info
            }
          }
          break;
        }
        // Change Delay between
        case 2:{
          delayval = (unsigned int) frames.read(); // Makes the first byte the Delay time
          delayval = delayval << 8; // Shift up the first byte
          delayval += (unsigned int) frames.read(); // Adds the second byte to the Delay time
          break;
        }
  
        // Create New Device
        case 3:{ // Create New Device
          port = (int) frames.read(); // Read Device Port
          pixelsCount = (int) frames.read(); // Read How Many Pixels that device has
  
          CreateLedDevice(port, pixelsCount); // Creates the Device
          
          deviceNumPixels[port] = pixelsCount; // Record how many pixels
          break;
        }
        
        // Start and/or Wait for Next Frame
        case 4:{
          FastLED.show(); //Send the Updated Pixel Data to the Devices
          getSerialUpdates();
          currentTime = millis();
          if((currentTime - frameStartTime) < delayval){
            delay(delayval - (currentTime - frameStartTime));
          }
          else{
            Serial.print((currentTime - frameStartTime));
            Serial.print(" ");
            Serial.print(delayval);
            Serial.println(" FRAMES TAKING TOO LONG TO DRAW!!!");
          }
          frameStartTime = millis();
          
          break;
        }
      }
      if(forceNewFile){
        forceNewFile = false;
        break;
      }
    }
    // close the file:
    frames.close();
  } 
  else {
   // // if the file didn't open, print an error:
   Serial.print("error opening ");
   Serial.println(selectedFile);
   getSerialUpdates(); // Check for new File Commands
   delay(errorDelayVal); // Wait as to not spam console
  }
}