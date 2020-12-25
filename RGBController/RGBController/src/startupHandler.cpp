#include "Arduino.h"
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

#include "global.h"
#include "functions.h"

void initalizeLEDCommands(){
    if(SD.exists(startFileName)){
        File startFile = SD.open(startFileName); // Open Startup File
        startFile.readBytes(selectedFile, startFile.size()); // The only thing in the file should be the name of the file so read the whole file and write it to the selectedFile array
        if(!SD.exists(selectedFile)){ // Incase the file in the startup file doesnt exist create and run the default file.
            SD.remove(startFileName); // Delete the bad Startup file so that it will be regenerated
            
            // Create Startup File
            File startFile = SD.open(startFileName, FILE_WRITE); // Create startup file to write into
            for(int i = 0; i < strlen(defaultFileName); i++){
                startFile.write(defaultFileName[i]);
            }
            startFile.close(); // Close startup file

            if(!SD.exists(defaultFileName)){
                createDefaultFile();
            }
            createDefaultFile(); // Create the Defua
        }
        startFile.close(); // Close File after reading
    }
    else{
        // Create Startup File
        File startFile = SD.open(startFileName, FILE_WRITE); // Create startup file to write into
        for(int i = 0; i < strlen(defaultFileName); i++){
            startFile.write(defaultFileName[i]);
        }
        startFile.close(); // Close startup file

        if(!SD.exists(defaultFileName)){
            createDefaultFile();
        }
        charArrayWriter(selectedFile, (char*) defaultFileName); // Select the defaultFile as the file to read
    }
}

void createDefaultFile(){ // Creates the Default Pattern File

    File defaultFile = SD.open(defaultFileName, FILE_WRITE); // Create default file to write into

    defaultFile.write(4); // First Frame

    for(byte i=0; i < MAXPORTS; i++){
        defaultFile.write(3); // Create Device
        defaultFile.write(i); // Port Number of Device
        defaultFile.write(MAXPIXELS); // All Default File Devices have max LED length
    }

    defaultFile.write(2); // Set Delay of Frames
    // Write an equivalent of 5000ms delay across 2 bytes
    defaultFile.write(19);
    defaultFile.write(136);

    byte zero = 0; // Otherwise it is sending an ambigous value
    for(byte p=0; p < MAXPORTS; p++){
        defaultFile.write(zero); // RGB Code
        defaultFile.write(p); // Port P
        for(int s=0; s < 255; s++){
            defaultFile.write(zero); // Red = 0
            defaultFile.write(255); // Green = 255
            defaultFile.write(zero); // Blue = 0
        }
    }

    defaultFile.write(4); // Next Frame

    defaultFile.close(); // Close File
}