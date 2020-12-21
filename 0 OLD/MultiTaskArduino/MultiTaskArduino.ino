#include <Adafruit_NeoPixel.h>
#include <math.h>


#define PIN        3 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 9 // Popular NeoPixel ring size
#define LAYERS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Global Variables
int layerSteps[LAYERS];

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object
  pixels.setBrightness(255); 


  layerSteps[0] = 0;
  layerSteps[1] = 3;
  layerSteps[2] = 6;
}

void loop() {
  SetBlue(1);
  SetRed(0);
  SetGreen(2);
  delay(100);
}


// Functions to Call
void SetBlue(int layer){
  pixels.setPixelColor(layerSteps[layer], pixels.Color(0, 0, 100));
  pixels.show();
  IncrementControl(layer);
}
void SetRed(int layer){
  pixels.setPixelColor(layerSteps[layer], pixels.Color(100, 0, 0));
  pixels.show();
  IncrementControl(layer);
}
void SetGreen(int layer){
  pixels.setPixelColor(layerSteps[layer], pixels.Color(0, 100, 0));
  pixels.show();
  IncrementControl(layer);
}

void IncrementControl(int layer){
  if(layerSteps[layer] >= NUMPIXELS){
    layerSteps[layer] = 0;
  }
  else{
    layerSteps[layer]++;
  }
}
