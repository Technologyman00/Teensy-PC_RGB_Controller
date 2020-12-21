#include <Adafruit_NeoPixel.h>

byte incomingBytes[2];

void setup()
{
  Serial.begin(0); // USB is always 12 Mbit/sec
}

void loop()
{
  if(Serial.available()){
    if(readNoOfBytes(incomingBytes, 2)){
      Serial.print(incomingBytes[0]);
      Serial.print(incomingBytes[1]); 
    }
    delay(100);  // do not print too fast!
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
