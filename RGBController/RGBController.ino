#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

#define MAXPIXELS 255
#define MAXPORTS  40   

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
int pixelsCount = 255;

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
          port = frames.read(); // Read Device Port
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

void getSerialUpdates(){
  if(Serial.available() > 0){
    
    serialCommand = Serial.read(); // Read Command to act upon
    Serial.read(); // Read Space
    
    if(serialCommand == 'p'){ // Play File on SD card
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(selectedFile, lengthToRead); // Read the String and put it to a char array
      
      Serial.print("Will now play: ");
      Serial.println(selectedFile);
      
      forceNewFile = true; // Force new File to open
      frameStartTime = millis(); // Start new Frame Time
      
    }
    else if(serialCommand == 'w'){ // Write SD card File
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(workingFile, lengthToRead); // Read the String and put it to a char array
      if(SD.exists(workingFile)){ // Check if file exists
        Serial.println("File Already Exists.");
      }
      else {
        Serial.println("Starting File Writing.");
        forceNewFile = true;
        File newFile = SD.open(workingFile, FILE_WRITE);

        while(Serial.available() == 0); 
  
        lengthToRead = 0;
        for(int i = 0; i < 4; i++){
          while(Serial.available() == 0); // Wait for Data
          lengthToRead <<= 8; // Shift up the first byte
          lengthToRead += (unsigned int) Serial.read(); // Adds Bytes  
        }

        Serial.println(lengthToRead);
      
        for(int i = 0; i < lengthToRead; i++){
          while(Serial.available() == 0);
          newFile.write(Serial.read()); // Write what is read to file.
        }
        newFile.close(); // File is done.
        Serial.println("File is Written.");
        
      }
    }
    else if(serialCommand == 'd'){ // Delete SD card File
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(workingFile, lengthToRead); // Read the String and put it to a char array
      if(SD.exists(workingFile)){ // Check if file exists
        Serial.print("Are you sure you want to delete: ");
        Serial.print(workingFile);
        Serial.println("? (Y/N))");
        while(Serial.available() == 0){
         // Wait until there is a response
        }
        serialCommand = Serial.read(); // Read Response
        if(serialCommand == 'Y' || serialCommand == 'y'){
          SD.remove(workingFile);
          Serial.println("File Deleted.");
        }
        else{
          Serial.println("File Kept.");
        }
      }
      else{ // File Does Not Exist
        Serial.print(workingFile);
        Serial.println(" does not exist.");
      }
      
    }
    else if(serialCommand == 'l'){ // List SD card Files
      Serial.println("--------------------");
      File directory = SD.open("/");
      while(true){
        File entry = directory.openNextFile();

        if(!entry){
          break;
        }

        if (entry.isDirectory()){
          Serial.print(entry.name());
          Serial.println("/");
        } 
        else{
          Serial.print(entry.name());
          // files have sizes, directories do not
          Serial.print("\t\t");
          Serial.println(entry.size(), DEC);
        }
        entry.close();
      }
      Serial.println("--------------------");
    }
    else if(serialCommand == 's'){ // Show Input to Display a single Frame Live and not on SD Card
      
    }
  }
}

void charArrayWriter(char *arrayToBeWritten, char *arrayFrom){

  int arrayFromLength = strlen(arrayFrom);
  for(int i=0; i < arrayFromLength; i++){
    arrayToBeWritten[i] = arrayFrom[i];
  }
  arrayToBeWritten[arrayFromLength] = '\0';
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
