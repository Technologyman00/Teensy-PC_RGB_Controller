#include <Adafruit_NeoPixel.h>
#include <math.h>

#define PIN        3 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 10 // Popular NeoPixel ring size
#define LAYERS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Global Variables
int layerSteps[LAYERS];
int frameMax[LAYERS];

byte colors[NUMPIXELS * 3];

int red = 0;
int green = 0;
int blue = 0;

int loopCount = 0;

int LayerFrames [LAYERS][NUMPIXELS][3];

int numbofbytes = 0;

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object
  Serial.begin(19200);
}

void loop() {
  PlayLayerFrames(0);
  GetColor();
  //delay(100);
}


// Functions to Call
void PlayLayerFrames(int layer){
  for(int c=0; c < NUMPIXELS; c++){
    pixels.setPixelColor(c, pixels.Color(LayerFrames[layer][c][0], LayerFrames[layer][c][1], LayerFrames[layer][c][2]));
  }
  pixels.show();
  FrameControl(layer);
}

void FrameControl(int layer){
  if(layerSteps[layer] >= (frameMax[layer]-1)){
    layerSteps[layer] = 0;
  }
  else{
    layerSteps[layer]++;
  }
}

void GetColor(){
  if(Serial.readBytes(colors, NUMPIXELS * 3) != 0){
    for(int c=0; c < (NUMPIXELS); c++){
      for(int i=0; i < 3; i++){
       LayerFrames[0][c][i] = (int) colors[(c*3)+i];
       //Serial.println(colors[c+i]);
      }
    }
     //Serial.println(color);
  }
}
