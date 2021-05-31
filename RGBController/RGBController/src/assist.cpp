#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
#include <math.h>

#include "global.h"
#include "functions.h"

#ifdef PARALLEL
  #include <OctoWS2811.h>
#else
  #include <FastLED.h>
#endif


void softRestart(){
  Serial.end();  //clears the serial monitor  if used
  frames.close(); //closes currently open file
  SCB_AIRCR = 0x05FA0004;  //write value for restart
}

void charArrayWriter(char *arrayToBeWritten, char *arrayFrom){

  int arrayFromLength = strlen(arrayFrom);
  for(int i=0; i < arrayFromLength; i++){
    arrayToBeWritten[i] = arrayFrom[i];
  }
  arrayToBeWritten[arrayFromLength] = '\0';
}

// Time to Delay While checking for Serial updates
void smartDelay(int delayMS){
  unsigned long startSmartDelay = millis();
  while((millis()-delayMS) < startSmartDelay){
    getSerialUpdates(); // Check if there is a Serial Command to handle
    if(forceNewFile){
      break; // Stop Delay if there is a new file request.
    }
    delay(delayStep);
  }
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

int GetLEDStart(int port){
  #ifdef PARALLEL
    return (port * MAXPIXELS);
  #else
    return 0;
  #endif
}


void CreateLedDevice(int portForDevice, int pixelsInDevice){
  #ifndef PARALLEL
  // Nasty Dirty Hack for Creating the devices as they require a const for the port but thats not how it works here.
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
  #endif
}