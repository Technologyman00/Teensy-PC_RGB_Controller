#include <Adafruit_NeoPixel.h>
#include <SD.h>
#include <SPI.h>

#define FRAMES 2
#define PORTS 10
#define MAX_PIXELS 31 // Popular NeoPixel ring size
#define COLORS_PER_LED 3 // 3 for RGB 4 for RGBW
#define FRAME_TIME 1000

Adafruit_NeoPixel Devices[PORTS];

const int chipSelect = BUILTIN_SDCARD;

//Global Variables
byte PixelsData[FRAMES][PORTS][MAX_PIXELS][COLORS_PER_LED];
byte PixelsSelected[1]; // Needs to be array but only uses 1 byte

byte PixelsConfig[2]; //Startup Configuration

byte DeviceConfig[PORTS];

byte DeviceSelected;
byte FrameSelected;
byte ColorRead[3] = {0, 0, 0};

bool SetupDone = false;

void setup() {
  Serial.begin(0);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  //Serial.setTimeout(50);
}

void loop() {
    switch (Serial.read()){ // Command Select
      case 1: //Create/Update Devices
        DeviceSelected = Serial.read(); // Device Select
        Devices[DeviceSelected] = Adafruit_NeoPixel(Serial.read(), DeviceSelected, NEO_GRB + NEO_KHZ800); // LED Length
        Devices[DeviceSelected].begin(); // INITIALIZE NeoPixel strip object
        Serial.print(DeviceSelected);
        break;

      case 2: // Send Colors Now
        DeviceSelected = Serial.read();
        for(int i=0; i < Devices[DeviceSelected].numPixels(); i++){
          readNoOfBytes(ColorRead, COLORS_PER_LED);
          Devices[DeviceSelected].setPixelColor(i, ColorRead[0], ColorRead[1], ColorRead[2]);
          Serial.print(ColorRead[0]);
        }
        Devices[DeviceSelected].show();
        break;

      case 3: // Write to Frame Buffer
        DeviceSelected = Serial.read();
        FrameSelected = Serial.read();
        for(int i=0; i < Devices[DeviceSelected].numPixels(); i++){
          readNoOfBytes(ColorRead, COLORS_PER_LED);
          PixelsData[FrameSelected][DeviceSelected][i][0] = ColorRead[0]; // Red LED
          PixelsData[FrameSelected][DeviceSelected][i][1] = ColorRead[1]; // Green LED
          PixelsData[FrameSelected][DeviceSelected][i][2] = ColorRead[2]; // Blue LED
        }
        break;

      case 4: // Play Frames *** LOCKS LOOP TO HERE UNTIL EXIT CODE IS SENT ***
        while(Serial.read() != 255){
          for(int frame=0; frame < FRAMES; frame++){
            for(int port=0; port < PORTS; port++){
              for(int i=0; i < Devices[port].numPixels(); i++){
                Devices[port].setPixelColor(i, PixelsData[frame][port][i][0], PixelsData[frame][port][i][1], PixelsData[frame][port][i][2]);
              }
              Devices[port].show();
            }
            delay(FRAME_TIME);
          }
        }
        break;

        
    }
   
    delay(10);
}

void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<Devices[3].numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / Devices[3].numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      Devices[3].setPixelColor(i, Devices[3].gamma32(Devices[3].ColorHSV(pixelHue)));
    }
    Devices[3].show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<Devices[3].numPixels(); i++) { // For each pixel in strip...
    Devices[3].setPixelColor(i, color);         //  Set pixel's color (in RAM)
    Devices[3].show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
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

  
