#include <Adafruit_NeoPixel.h>
#include <math.h>


#define PIN        3 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 9 // Popular NeoPixel ring size
#define LAYERS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Global Variables
int layerSteps[LAYERS];
int frameMax[LAYERS];


int LayerFrames [LAYERS][10][NUMPIXELS][3];
/*
int Layer0Frames [10][NUMPIXELS][3] = 
{{{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}, 
{{255, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}, 
{{255, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}, 
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}, 
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}, 
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 0}},
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 0, 0}},
{{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}}};
*/
void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object
  pixels.setBrightness(255); 

  Serial.begin(9600);

  frameMax[0] = 10;
  for(int s=0; s < frameMax[0]; s++){
    for(int p=0; p < NUMPIXELS; p++){
      for(int c=0; c < 3; c++){
        LayerFrames[0][s][p][c] = 50;
      }
    }
  }
}

void loop() {
  PlayLayerFrames(0);
  delay(1000);
}


// Functions to Call
/*
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
*/
void PlayLayerFrames(int layer){
  for(int c=0; c < NUMPIXELS; c++){
    pixels.setPixelColor(c, pixels.Color(LayerFrames[layer][layerSteps[layer]][c][0], LayerFrames[layer][layerSteps[layer]][c][1], LayerFrames[layer][layerSteps[layer]][c][2]));
  }
  pixels.show();
  FrameControl(layer);
}

void IncrementControl(int layer){
  if(layerSteps[layer] >= NUMPIXELS){
    layerSteps[layer] = 0;
  }
  else{
    layerSteps[layer]++;
  }
}
void FrameControl(int layer){
  if(layerSteps[layer] >= (frameMax[layer]-1)){
    layerSteps[layer] = 0;
  }
  else{
    layerSteps[layer]++;
  }
}
