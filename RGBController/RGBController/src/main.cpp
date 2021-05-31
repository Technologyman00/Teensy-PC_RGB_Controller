#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
#include <math.h>

#include "global.h"
#include "functions.h"

#ifdef PARALLEL
  #include <OctoWS2811.h>
  // Any group of digital pins may be used
  // In Version 2 of the PCB pin 13 that drive the LED was removed as it should be controlled independently
  byte pinList[40] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};

  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  DMAMEM int displayMemory[MAXPIXELS * MAXPORTS * 3 / 4];
  int drawingMemory[MAXPIXELS * MAXPORTS * 3 / 4];

  const int config = WS2811_GRB | WS2811_800kHz;

  OctoWS2811 leds(MAXPIXELS, displayMemory, drawingMemory, config, MAXPORTS, pinList);
#else
  #include <FastLED.h>
  CRGB Device[MAXPORTS][MAXPIXELS]; // Data for LEDS
#endif

byte deviceNumPixels[MAXPORTS]; // Number of Pixels per Device

File frames; // Frames File Open
char selectedFile[255]; // Name of Frames file
char workingFile[255]; // Name of file being when using serial commands

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
const unsigned int errorDelayVal = 1000; // Time to pause between alerting errors for opening files
const unsigned int delayStep = 1; // Time to pause between checking for Serial Commands inside Smart Delay

byte red = 0; // Temp Storage for Red Part of LED
byte green = 0; // Temp Storage for Green Part of LED
byte blue = 0; // Temp Storage for Blue Part of LED

byte hue = 0; // Temp Storage for Hue Value
byte sat = 0; // Temp Storage for Saturation Value
byte value = 0; // Temp Storage for Value Value

byte commandSelect = 255; // Selected Command from File
byte port = 255; // Selected Port
int pixelsCount = 0; // Number of Pixels as Pulled from deviceNumPixels
int pixelsStart = 0;

unsigned long frameStartTime = 0; // Time when frame started
unsigned long currentTime = 0; // Time when frame ended

char serialCommand = 'A'; // Command Char from Serial
int lengthToRead = 0; // length to Read from Serial for file transfer

int badFrames = 0; // Count of Bad Frames gets reset when displayed to user
int framesPassed = 0; // Count of Frames Get Reset when reaches numbOfFramesTillAlert
const int numbOfFramesTillAlert = 10; // Frames till alerting user how many bad frames passed

bool forceNewFile = false; // If a new file is forced

const int numbOfLoopsTillSerialCheck = 10; // Number of loops till checking for serial commands
int loopCount = 0; // Count of Loops passed Gets Reset when reaches numbOfLoopsTillSerialCheck

const char startFileName[12] = "startup.txt";
const char defaultFileName[12] = "default.txt"; 

int statusLED = 13; // LED on the Teensy

void setup(){

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

  //Set Default file
  //charArrayWriter(selectedFile, (char*) "frames4.txt"); // Old way with a hardcoded default file name
  initalizeLEDCommands(); //Reads a startup file first to know which pattern to open by default
  #ifdef PARALLEL
    leds.begin();
  #endif

  pinMode(statusLED, OUTPUT); // Set the status LED to be an output.
  digitalWrite(statusLED, LOW); // Annoying for it to always be on because there is an external power source. 

  frameStartTime = millis(); // Start the First Frame time
}

void loop(){
	// re-open the file for reading:
  frames = SD.open(selectedFile);
  if(frames){
    // read from the file until there's nothing else in it:
    while(frames.available()){

      loopCount++; // Increment LoopCount
      if(loopCount >= numbOfLoopsTillSerialCheck){ // Check if time to check serial updates
        getSerialUpdates(); // Check if there is a Serial Command to handle
        loopCount = 0;
      }
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
            pixelsStart = GetLEDStart(port);
            pixelsCount += pixelsStart;
            for(int i=pixelsStart; i < pixelsCount; i++){
              red = frames.read(); // Read Red Val
              green = frames.read(); // Read Green Val
              blue = frames.read();  // Read Blue Val

              #ifdef PARALLEL
                leds.setPixel(i, red, green, blue);
              #else
                Device[port][i] = CRGB(-red+255, -green+255, -blue+255); // Update RAM for Pixels Info
              #endif

              if(forceNewFile){ // Break for loop if Requested by User
                break; // Causes for loop escape
              }
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
            pixelsStart = GetLEDStart(port);
            pixelsCount += pixelsStart;
            for(int i=pixelsStart; i < pixelsCount; i++){
              hue = frames.read(); // Read Hue Val
              sat = frames.read(); // Read Saturation Val
              value = frames.read();  // Read Value Val
              HSVtoRGB(hue, sat, value); // Convert HSV to RGB // Updates Global RGB values

              #ifdef PARALLEL
                leds.setPixel(i, red, green, blue);
              #else
                Device[port][i] = CRGB(-red+255, -green+255, -blue+255); // Update RAM for Pixels Info
              #endif

              if(forceNewFile){ // Break for loop if Requested by User
                break; // Causes for loop escape
              }
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
          port = frames.read(); // Read Device Port
          pixelsCount = frames.read(); // Read How Many Pixels that device has
  
          CreateLedDevice(port, pixelsCount); // Creates the Device
          
          deviceNumPixels[port] = pixelsCount; // Record how many pixels
          break;
        }
        
        // Start and/or Wait for Next Frame
        case 4:{
          #ifdef PARALLEL
                leds.show();
                //while (leds.busy()){ // Wait until all sending has completed
                //  smartDelay(1);
                //}
          #else
                FastLED.show(); //Send the Updated Pixel Data to the Devices
          #endif

          currentTime = millis(); // Update the Current Time
          framesPassed++; // Increment Frame Counter
          if((currentTime - frameStartTime) < delayval){ // See if the time took less than it should for a single frame.
            smartDelay(delayval - (currentTime - frameStartTime)); // Wait the remaning time and Check for Serial Commands
          }
          else{ 
            badFrames++; // Increment bad Frame Counter
          }
          if(framesPassed >= numbOfFramesTillAlert){ // Check if correct number of Frames have passed.
            framesPassed = 0; // Reset Frame Counter.
            if(badFrames > 0){ // Check if number of bad frames is greater than 0.
              // Alert User that it takes too long to update frames if done constantly
                Serial.print(badFrames);
                Serial.println(" FRAME(S) TAKING TOO LONG TO DRAW!!!");
                
                badFrames = 0; // Reset Frame counter 
            }
          }
          frameStartTime = millis(); // Update Frame Start Time
          break;
        }
      }
      if(forceNewFile){ // Break While loop if Requested by User
        forceNewFile = false; // Reset force new file bool
        break; // Causes while loop escape and to close the currently open file to either refresh the file or open a new file.
      }
    }
    // close the file:
    frames.close();
  } 
  else {
   // // if the file didn't open, print an error:
   Serial.print("error opening ");
   Serial.println(selectedFile);
   smartDelay(errorDelayVal); // Wait as to not spam console and Check for Serial Commands
  }
}