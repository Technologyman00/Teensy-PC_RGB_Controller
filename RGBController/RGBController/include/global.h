#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arduino.h"
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

#define MAXPIXELS 255
#define MAXPORTS  40   

extern CRGB Device[MAXPORTS][MAXPIXELS];

extern byte deviceNumPixels[MAXPORTS];

extern File frames;
extern char selectedFile[255];
extern char workingFile[255];

extern const int chipSelect;

extern unsigned int delayval; // Time (in milliseconds) to pause between pixels
extern const unsigned int errorDelayVal; // Time to pause between alerting errors for opening files
extern const unsigned int delayStep; // Time to pause between checking for Serial Commands inside Smart Delay

extern byte red;
extern byte green;
extern byte blue;

extern byte hue;
extern byte sat;
extern byte value;

extern byte commandSelect;
extern byte port;

extern int pixelsCount;

extern unsigned long frameStartTime;
extern unsigned long currentTime;

extern char serialCommand;
extern int lengthToRead;

extern bool forceNewFile;

#endif