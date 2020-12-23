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
    
    if(serialCommand == 'p'){ // Play File on SD card
      
      lengthToRead = Serial.available()+1; //Save how many Serial Bytes to Read. +1 because it would always miss the last character
      Serial.readString().toCharArray(selectedFile, lengthToRead); // Read the String and put it to a char array
      
      Serial.print("Will now play: ");
      Serial.println(selectedFile);
      
      forceNewFile = true; // Force new File to open
      frameStartTime = millis(); // Start new Frame Time
      
    }
    else if(serialCommand == 'w'){ // Write SD card File
      
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
    else if(serialCommand == 'd'){ // Delete SD card File
      
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
    else if(serialCommand == 'l'){ // List SD card Files
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
    else if(serialCommand == 's'){ // Show Input to Display a single Frame Live and not on SD Card
      
    }
  }
}