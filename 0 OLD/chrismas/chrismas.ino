// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <math.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        3 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 9 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 250 // Time (in milliseconds) to pause between pixels

long Rand = -1;

void setup() {

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(255); 
  
}

void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'
  Rand = random(0, 3);
  Rand = round(Rand);

  if(Rand == 0){
    Fade2Color(pixels.Color(255, 0, 0), pixels.Color(0, 255, 0), 10); // Red to Green
    colorWipe(pixels.Color(255, 0, 0), 100); // Red
    colorWipe(pixels.Color(0, 255, 0), 100); // Green
    Fade2Color(pixels.Color(0, 255, 0), pixels.Color(255, 0, 0), 10); // Green to Red
    colorWipe(pixels.Color(0, 255, 0), 100); // Green
    colorWipe(pixels.Color(255, 0, 0), 100); // Red
  }
  else if(Rand == 1){
    theaterChase(pixels.Color(255,   0,   0), 200); // Red
    Fade2Color(pixels.Color(255, 0, 0), pixels.Color(0, 255, 0), 10); // Red to Green
    theaterChase(pixels.Color(  0,   255, 0), 200); // Green
    Fade2Color(pixels.Color(0, 255, 0), pixels.Color(255, 0, 0), 10); // Green to Red
  }
  else if(Rand == 2){
    colorWipe(pixels.Color(255, 0, 0), 100); // Red
    colorWipe(pixels.Color(0, 255, 0), 100); // Green
    colorWipe(pixels.Color(255, 0, 0), 100); // Red
  }
  
  
}
void FadeInOut(uint32_t c1, uint32_t c2, int wait){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, c1);
    pixels.show();
  }
  for(int c=0; c<254; c++) {
    pixels.setBrightness(255-c);
    pixels.show();
    delay(wait);
  }
  //pixels.clear(); // Set all pixel colors to 'off'
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, c2);
    pixels.show();
  }
  for(int c=1; c<255; c++) {
    pixels.setBrightness(c);
    pixels.show();
    delay(wait);
  }
  for(int c=0; c<254; c++) {
    pixels.setBrightness(255-c);
    pixels.show();
    delay(wait);
  }
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, c1);
    pixels.show();
  }
  for(int c=1; c<255; c++) {
    pixels.setBrightness(c);
    pixels.show();
    delay(wait);
  }
}
void Fade2Color(uint32_t c1, uint32_t c2, int wait){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, c1);
    pixels.show();
  }
  for(int c=0; c<254; c++) {
    pixels.setBrightness(255-c);
    pixels.show();
    delay(wait);
  }
  //pixels.clear(); // Set all pixel colors to 'off'
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, c2);
    pixels.show();
  }
  for(int c=1; c<255; c++) {
    pixels.setBrightness(c);
    pixels.show();
    delay(wait);
  }
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) { // For each pixel in strip...
    pixels.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      pixels.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) {
        pixels.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      pixels.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}
/*
 * 
 * pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 255, 0));
    pixels.setPixelColor(3, pixels.Color(0, 255, 0));
    pixels.setPixelColor(4, pixels.Color(255, 0, 0));
    pixels.setPixelColor(5, pixels.Color(255, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 255, 0));
    pixels.setPixelColor(7, pixels.Color(0, 255, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop

    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.setPixelColor(2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 255, 0));
    pixels.setPixelColor(4, pixels.Color(0, 255, 0));
    pixels.setPixelColor(5, pixels.Color(255, 0, 0));
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 255, 0));
    
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop

    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    pixels.setPixelColor(2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(3, pixels.Color(255, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 255, 0));
    pixels.setPixelColor(5, pixels.Color(0, 255, 0));
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.setPixelColor(7, pixels.Color(255, 0, 0));
    
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop

    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    pixels.setPixelColor(2, pixels.Color(0, 255, 0));
    pixels.setPixelColor(3, pixels.Color(255, 0, 0));
    pixels.setPixelColor(4, pixels.Color(255, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 255, 0));
    pixels.setPixelColor(6, pixels.Color(0, 255, 0));
    pixels.setPixelColor(7, pixels.Color(255, 0, 0));
    
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
 */
