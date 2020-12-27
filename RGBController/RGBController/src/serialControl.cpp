#include "Arduino.h"
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

#include "global.h"
#include "functions.h"

void getSerialUpdates(){
  if(Serial.available() > 0){
    
    serialCommand = Serial.read(); // Read Command to act upon
    Serial.read(); // Read Space
    
    if(serialCommand == 'p' || serialCommand == 'P'){ // Play File on SD card
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(selectedFile, lengthToRead); // Read the String and put it to a char array
      
      Serial.print("Will now play: ");
      Serial.println(selectedFile);
      
      forceNewFile = true; // Force new File to open
    }
    else if(serialCommand == 'w' || serialCommand == 'W'){ // Write SD card File
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(workingFile, lengthToRead); // Read the String and put it to a char array
      if(SD.exists(workingFile)){ // Check if file exists
        Serial.println("File Already Exists.");
      }
      else {
        Serial.println("Starting File Writing.");
        forceNewFile = true;
        File newFile = SD.open(workingFile, FILE_WRITE);

        while(Serial.available() == 0); 
  
        lengthToRead = 0;
        for(int i = 0; i < 4; i++){
          while(Serial.available() == 0); // Wait for Data
          lengthToRead <<= 8; // Shift up the first byte
          lengthToRead += (unsigned int) Serial.read(); // Adds Bytes  
        }

        Serial.println(lengthToRead);
      
        for(int i = 0; i < lengthToRead; i++){
          while(Serial.available() == 0);
          newFile.write(Serial.read()); // Write what is read to file.
        }
        newFile.close(); // File is done.
        Serial.println("File is Written.");
        
      }
    }
    else if(serialCommand == 's' || serialCommand == 'S'){ // Change Startup file

      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(workingFile, lengthToRead); // Read the String and put it to a char array

      createStartupFile(workingFile);

      Serial.print(workingFile);
      Serial.println(" will now be played on startup.");
    }
    else if(serialCommand == 'x' || serialCommand == 'X'){ // Delete SD card File
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(workingFile, lengthToRead); // Read the String and put it to a char array
      if(SD.exists(workingFile)){ // Check if file exists
        Serial.print("Are you sure you want to delete: ");
        Serial.print(workingFile);
        Serial.println("? (Y/N))");
        while(Serial.available() == 0){
         // Wait until there is a response
        }
        serialCommand = Serial.read(); // Read Response
        if(serialCommand == 'Y' || serialCommand == 'y'){
          SD.remove(workingFile);
          Serial.println("File Deleted.");
        }
        else{
          Serial.println("File Kept.");
        }
      }
      else{ // File Does Not Exist
        Serial.print(workingFile);
        Serial.println(" does not exist.");
      }
      
    }
    else if(serialCommand == 'l' || serialCommand == 'L'){ // List SD card Files
      Serial.println("--------------------");
      File directory = SD.open("/");
      while(true){
        File entry = directory.openNextFile();

        if(!entry){
          break;
        }

        if (entry.isDirectory()){
          Serial.print(entry.name());
          Serial.println("/");
        } 
        else{
          Serial.print(entry.name());
          // files have sizes, directories do not
          Serial.print("\t\t");
          Serial.println(entry.size(), DEC);
        }
        entry.close();
      }
      Serial.println("--------------------");
    }
    else if(serialCommand == 'n' || serialCommand == 'N'){ // Create a new Device
      while(Serial.available() == 0);
      port = Serial.read(); // Read Port
      while(Serial.available() == 0); 
      pixelsCount = Serial.read(); // Read Number of Pixels
      CreateLedDevice(port, pixelsCount); // Create Device
      deviceNumPixels[port] = pixelsCount; // Save Number of Pixels
    }
    else if(serialCommand == 'd' || serialCommand == 'D'){ // Show Input to Display a single Frame Live and not on SD Card
      while(true){
        while(Serial.available() == 0);
        serialCommand = Serial.read();

        if(serialCommand == 'X' || serialCommand == 'x'){
          break; // Exit the while loop
        }

        while(Serial.available() == 0);
        port = Serial.read();
        pixelsCount = deviceNumPixels[port];
        if(pixelsCount == 0){ // No device should have 0 pixels
          Serial.print("Device: ");
          Serial.print(port);
          Serial.println(" not setup!");
        }
        else { // Update Pixels
          if(serialCommand == 0){ // RGB Command
            for(int i=0; i < pixelsCount; i++){
              while(Serial.available() < 3);
              red = Serial.read(); // Read Red Val
              green = Serial.read(); // Read Green Val
              blue = Serial.read();  // Read Blue Val

              Device[port][i] = CRGB(-red+255, -green+255, -blue+255); // Update RAM for Pixels Info
            }
            FastLED.show(); //Send the Updated Pixel Data to the Devices
          }
          else if(serialCommand == 1){ //HSV Command
            for(int i=0; i < pixelsCount; i++){
              while(Serial.available() < 3);
              hue = Serial.read(); // Read Hue Val
              sat = Serial.read(); // Read Saturation Val
              value = Serial.read();  // Read Value Val
              HSVtoRGB(hue, sat, value); // Convert HSV to RGB

              Device[port][i] = CRGB(-red+255, -green+255, -blue+255); // Update RAM for Pixels Info
            }
            FastLED.show(); //Send the Updated Pixel Data to the Devices
          }
        }
      }
    }
    else if(serialCommand == 'r' || serialCommand == 'R'){ // Restart Controller
      softRestart();
    }
  }
}