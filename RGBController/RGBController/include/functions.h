#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#include "Arduino.h"
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>
#include "global.h"

void HSVtoRGB(byte H_byte, byte S_byte, byte V_byte);
void CreateLedDevice(int portForDevice, int pixelsInDevice);
void getSerialUpdates();
void charArrayWriter(char *arrayToBeWritten, char *arrayFrom);


#endif  // FUNCTIONS_H