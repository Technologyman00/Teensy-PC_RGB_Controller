#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
#include <math.h>

#define MAXPIXELS 100
#define MAXPORTS  40

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Application Interrupt and Reset Control location

#define PARALLEL // Comment out if to use Series FastLED sending instead of OctoWS2811

#ifdef PARALLEL
  #include <OctoWS2811.h>
  extern OctoWS2811 leds;
#else
  #include <FastLED.h>
  extern CRGB Device[MAXPORTS][MAXPIXELS];
#endif

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
extern int pixelsStart;

extern unsigned long frameStartTime;
extern unsigned long currentTime;

extern char serialCommand;
extern int lengthToRead;

extern bool forceNewFile;

extern const char startFileName[12];
extern const char defaultFileName[12];

#endif