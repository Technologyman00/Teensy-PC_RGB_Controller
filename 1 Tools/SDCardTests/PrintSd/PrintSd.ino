#include <Adafruit_NeoPixel.h> 
#include <SD.h>
#include <SPI.h>

#define PIN       3 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 9 // Popular NeoPixel ring size
#define PORTS     13

Adafruit_NeoPixel Devices[PORTS];

#define DELAYVAL 1000 // Time (in milliseconds) to pause between pixels

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

byte Red;
byte Green;
byte Blue;

byte Lines;

void setup(){
  for(int i=0; i < PORTS; i++){
    Devices[i] = Adafruit_NeoPixel(9, i, NEO_GRB + NEO_KHZ800); // LED Length
    Devices[i].begin(); // INITIALIZE NeoPixel strip object
  }

 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while(!Serial){
    
  }

  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    while(myFile.available()){
      Serial.println(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
void loop(){
	
}
