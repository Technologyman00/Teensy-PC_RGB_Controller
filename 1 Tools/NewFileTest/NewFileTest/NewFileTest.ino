#include <SD.h>
#include <SPI.h>

File myFile;
const int chipSelect = BUILTIN_SDCARD;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    
  }

  delay(1000);

   if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }

  // re-open the file for reading:
  myFile = SD.open("bytes.txt");
  if (myFile) {
    while(myFile.available()){
      Serial.println((byte) myFile.read());
     }
    // close the file:
    myFile.close();
  } 
  else {
   // // if the file didn't open, print an error:
   Serial.println("error opening test.txt");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
