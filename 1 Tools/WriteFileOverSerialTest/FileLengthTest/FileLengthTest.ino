#include <SD.h>
#include <SPI.h>

unsigned int lengthToRead = 0;
char workingFile[255];
byte readDatas = 0;

const int chipSelect = BUILTIN_SDCARD;

void setup() {
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }

  delay(10);
  
  Serial.begin(9600);
  Serial.setTimeout(0);
  if(!Serial){
    
  }
  while(Serial.available() == 0); 
  File newFile = SD.open("test1.txt", FILE_WRITE);
  while(Serial.available() == 0); 
  
  lengthToRead = 0;
  for(int i = 0; i < 4; i++){
    while(Serial.available() == 0); // Wait for Data
    lengthToRead <<= 8; // Shift up the first byte
    readDatas = Serial.read();
    lengthToRead += (unsigned int) readDatas; // Adds Bytes  
  }

  for(int i = 0; i < lengthToRead; i++){
    while(Serial.available() == 0);
    newFile.write(Serial.read()); // Write what is read to file.
  }
  newFile.close(); // File is done.
  
}

void loop() {
  Serial.println("DONE!");

}
