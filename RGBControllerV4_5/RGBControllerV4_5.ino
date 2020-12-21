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
#include <math.h>

#define MAXPIXELS 255
#define MAXPORTS  40   

CRGB Device[MAXPORTS][MAXPIXELS];

byte deviceNumPixels[MAXPORTS];

File frames;
char *selectedFile = "frames2.txt";

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

byte red = 0;
byte green = 0;
byte blue = 0;

byte hue = 0;
byte sat = 0;
byte value = 0;

byte commandSelect = 255;
byte port = 255;
int pixelsCount = 255;

unsigned long frameStartTime = 0;
unsigned long currentTime = 0;

char *serialCommand = "AAAAAAAAAAAAAAAAAAAAA";
char *test = "AAAAAAAAAAAAAAAAAAAAA";
int lengthToRead;

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

  frameStartTime = millis(); // Start the First Frame time
}
void loop(){
	// re-open the file for reading:
  frames = SD.open(selectedFile);
  if (frames) {
    // read from the file until there's nothing else in it:
    while(frames.available()){
      if(Serial.available() > 0){
        lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
        Serial.readString().toCharArray(serialCommand, lengthToRead); // Read the String and put it to a char array
        Serial.println(serialCommand);
        readUntilSpace(&serialCommand, &test);
        Serial.println(test);
        Serial.println(serialCommand);
      }
      switch (frames.read()){ // Read Command

        // RGB Color Sending
        case 0:
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
  
        // HSV Color Sending
        case 1:
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
  
        // Change Delay between
        case 2:
          Serial.println("CASE 2");
          delayval = (unsigned int) frames.read(); // Makes the first byte the Delay time
          delayval = delayval << 8; // Shift up the first byte
          delayval += (unsigned int) frames.read(); // Adds the second byte to the Delay time
          delayval = 1000;
          break;
  
        // Create New Device
        case 3: // Create New Device
          port = frames.read(); // Read Device Port
          pixelsCount = (int) frames.read(); // Read How Many Pixels that device has
  
          CreateLedDevice(port, pixelsCount); // Creates the Device
          
          deviceNumPixels[port] = pixelsCount; // Record how many pixels
          break;
  
        // Start and/or Wait for Next Frame
        case 4:
          FastLED.show(); //Send the Updated Pixel Data to the Devices
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
    // close the file:
    frames.close();
  } 
  else {
   // // if the file didn't open, print an error:
   Serial.println("error opening test.txt");
  }
}

/// FIIXXXXXXX
void readUntilSpace(char **charsToParse, char **firstWord){ // Would rather split string like Java or Python but here we are
  int lengthOfString = strlen(*charsToParse); // Get the length of the Char Array
  int spacePos = 0; // Variable for where the space is

  // Find the first Space in the Char Array
  for(int i=0; i < lengthOfString; i++){
    if(charsToParse[0][i] == ' '){ // Sets to the Pointer of the Char array read in.
      spacePos = i; // save location of space
      break; // exit for loop because only first space is needed
    }
  }

  //Create Space for the first word of the read in char array
  //char spaceBuild[spacePos+1]; // Build Char array to allocate space and add 1 for end array command
  //firstWord[0] = spaceBuild; // Set output array to new size
  
  
  for(int i=0; i < spacePos; i++){
    firstWord[0][i] = charsToParse[0][i]; // Write to output Array character by character
  }
  firstWord[0][spacePos] = '\0'; // End Array
  
  spacePos++; // Increment spacePos to count up to the Space
  char charsToParseNew[(lengthOfString - spacePos)];
  

  for(int i=spacePos; i < lengthOfString; i++){
    charsToParseNew[i-spacePos] = charsToParse[0][i];
  }
  
  for(int i=0; i < (lengthOfString - spacePos); i++){
    charsToParse[0][i] = charsToParseNew[i]; // Does not change the size properly....
  }
  charsToParse[(lengthOfString - spacePos)] = '\0';
}

void HSVtoRGB(byte H_byte, byte S_byte, byte V_byte){
  
  double H = (((double) H_byte) / 255) * 360;

  double V = ((double) V_byte) / 255;
  double S = ((double) S_byte) / 255;

  double C = V * S;

  double X_HSV = C * (1 - abs((fmod( (H / 60.0 ) , 2.0) - 1)));
  
  double m = V - C;

  if(H < 60){
    red = (byte) ((C+m)*255);
    green = (byte) ((X_HSV+m)*255);
    blue = 0;
    
  } else if(H < 120){
    red = (byte) ((X_HSV+m)*255);
    green = (byte) ((C+m)*255);
    blue = 0;

  } else if(H < 180){
    red = 0; 
    green = (byte) ((C+m)*255);
    blue = (byte) ((X_HSV+m)*255);

  } else if(H < 240){
    red = 0; 
    green = (byte) ((X_HSV+m)*255);
    blue = (byte) ((C+m)*255);

  } else if(H < 300){
    red = (byte) ((X_HSV+m)*255);
    green = 0;
    blue = (byte) ((C+m)*255);

  } else{
    red = (byte) ((C+m)*255);
    green = 0;
    blue = (byte) ((X_HSV+m)*255);
  }
  
}

// Nasty Dirty Hack for Creating the devices as they require a const for the port but thats not how it works here.
void CreateLedDevice(byte portForDevice, byte pixelsInDevice){
  // I hate this more than you do. I would much rather cast port to a const but I cant seem to get it working.
  switch (portForDevice){
    case 1:
      FastLED.addLeds<NEOPIXEL, 1>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 2:
      FastLED.addLeds<NEOPIXEL, 2>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 3:
      FastLED.addLeds<NEOPIXEL, 3>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 4:
      FastLED.addLeds<NEOPIXEL, 4>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 5:
      FastLED.addLeds<NEOPIXEL, 5>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 6:
      FastLED.addLeds<NEOPIXEL, 6>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 7:
      FastLED.addLeds<NEOPIXEL, 7>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 8:
      FastLED.addLeds<NEOPIXEL, 8>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 9:
      FastLED.addLeds<NEOPIXEL, 9>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 10:
      FastLED.addLeds<NEOPIXEL, 10>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 11:
      FastLED.addLeds<NEOPIXEL, 11>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 12:
      FastLED.addLeds<NEOPIXEL, 12>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 13:
      FastLED.addLeds<NEOPIXEL, 13>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 14:
      FastLED.addLeds<NEOPIXEL, 14>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 15:
      FastLED.addLeds<NEOPIXEL, 15>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 16:
      FastLED.addLeds<NEOPIXEL, 16>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 17:
      FastLED.addLeds<NEOPIXEL, 17>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 18:
      FastLED.addLeds<NEOPIXEL, 18>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 19:
      FastLED.addLeds<NEOPIXEL, 19>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 20:
      FastLED.addLeds<NEOPIXEL, 20>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 21:
      FastLED.addLeds<NEOPIXEL, 21>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 22:
      FastLED.addLeds<NEOPIXEL, 22>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 23:
      FastLED.addLeds<NEOPIXEL, 23>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 24:
      FastLED.addLeds<NEOPIXEL, 24>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 25:
      FastLED.addLeds<NEOPIXEL, 25>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 26:
      FastLED.addLeds<NEOPIXEL, 26>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 27:
      FastLED.addLeds<NEOPIXEL, 27>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 28:
      FastLED.addLeds<NEOPIXEL, 28>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 29:
      FastLED.addLeds<NEOPIXEL, 29>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 30:
      FastLED.addLeds<NEOPIXEL, 30>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 31:
      FastLED.addLeds<NEOPIXEL, 31>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 32:
      FastLED.addLeds<NEOPIXEL, 32>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 33:
      FastLED.addLeds<NEOPIXEL, 33>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 34:
      FastLED.addLeds<NEOPIXEL, 34>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 35:
      FastLED.addLeds<NEOPIXEL, 35>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 36:
      FastLED.addLeds<NEOPIXEL, 36>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 37:
      FastLED.addLeds<NEOPIXEL, 37>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 38:
      FastLED.addLeds<NEOPIXEL, 38>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
    case 39:
      FastLED.addLeds<NEOPIXEL, 39>(Device[portForDevice], pixelsInDevice); // Create Device
      break;
  }
}
