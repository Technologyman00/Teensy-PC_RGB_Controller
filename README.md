# Teensy-PC_RGB_Controller
 
The whole Idea behind this project was to create a much better RGB controller than the controllers or motherboard software I have seen. Currently It has already met that goal as it can play any pattern for many LEDs and up to individual 40 devices. I am still working on the user interface and many qualities of life things, but the main functionality does work. HOWEVER, it will need a PCB made to power all the LEDs as a Teensy cannot power that many safely.

## Features

- No Extra load on the CPU. The teensy has its own built in CPU that will handle all the commands to the ARGB devices.
- Store Loads of Patterns or Huge animations. The teensy uses an SD card to save and read all the patterns allowing for a huge number of patterns to be saved.
- Up to 40 ports. Most Controllers top out at a maximum of 4 ports. The teensy has 40! This allows each device to do its own individual pattern.
- Any pattern! There are no limitations on what can be displayed because it plays back frames allowing an almost infinite amount of customization. 
- Standard Plugs! This uses the regular 3 pin 5V ARGB connectors so any device with the same connector can be used!
- OPEN SOURCE! Are you a bit handier than most? You can change anything you would ever what about this project!

## Documentation
### Pattern Files

Description | Command | Argument 1 | Argument 2
------------ | -------------| ------------ | -------------|
Send RGB Command: | 0 | Port Number | Color Data |
Send HSV Command: | 1 | Port Number | Color Data |
Change Frame Delay: | 2 | Delay (2 Bytes) | N/A |
Create Device/Change Length: | 3 | Port Number | Number of Pixels |
Start New Frame: | 4 | N/A | N/A | N/A |

- Port 13 is not accessable from the hardware as it has the status LED so it was intentionally skipped in the PCB design. 

- Color Data is a continuous set of the RGB or HSV values. It will be (3 * Number of Pixels in Device) bytes long. For example it would go (Red Byte)(Blue Byte)(Green Byte)(Red Byte)(Blue Byte)(Green Byte)... or (Hue Byte)(Saturation Byte)(Value Byte)(Hue Byte)(Saturation Byte)(Value Byte)... All these bytes are from 0-255 with no decimals, as bytes are. For hue, saturation, and value these are all scaled to their corrective values.

- The delay value is split into 2 different bytes to allow a delay between 0 and 65535ms or 65.5 seconds. This allows a great range between quick animations and still colors. This value does not matter so much for still colors as the pattern file will just start over once it reaches the end re-displaying the same color.

### Serial Commands

Description | Command | Argument 1 | Argument 2 | Argument 3 |
------------ | -------------| ------------ | -------------| -------------|
Play File on SD Card: | P | File Name | N/A | N/A |
Write File to SD Card: | W | File Name | Length to Read (4 Bytes) | File Data |
Delete File on SD Card: | X | File Name | N/A | N/A |
List Files on SD Card: | L | N/A | N/A | N/A |
Change Startup File: | S | File Name | N/A | N/A |
Display Frame: | D | RGB or HSV -> (0 or 1) | Port Number | Color Data |
New Device: | N | Port | Number of Pixels | N/A |
Restart Teensy: | R | N/A | N/A | N/A |
Check Teensy Tempature: | T | N/A | N/A | N/A |

- File Name requires the file type *"example.txt"*
- File Data follows the documentation as setup in pattern files
- Length to Read is split into 4 bytes to allow very large files to be transferred (~4.3 GB) (if larger than ~4.3 GB just put the file onto the SD card manually)
- Color Data also follows the documentation as shown in pattern files
- ***Deleting files will ask if "Are sure you want to delete this?" A response is needed of Y/N before it will continue. Everything is halted when this is prompted.***
- ***Showing a Frame will not return to normal file reading until an exit command of X is sent.***

### Startup Handler

On startup the teensy will first read the *startup.txt* file which should contain the name of the file and only the name of the file. If this file does not exist or the code is unhappy with what was entered it will delete the *startup.txt* file and replace it with a *startup.txt* file that will run the default pattern file. The default pattern file sets all 40 ports to display Green on 255 pixels on those ports. This should make it so that it is obvious that the Teensy is working. The *startup.txt* file can be changed by either editing the file in a text editor or by sending the S command over serial.

## Updates
6/6
Full Deployment!!!!!
Example 1: https://youtu.be/utrNA2Hu2Kg
Example 2: https://youtu.be/6SqUPKUgLiA

5/30 Version 2 of the PCB was ordered and should be arriving shortly. This new version is to fix the concerns with the previous version, as the size was quite large and there was a design error. Both should be fixed in this version. Pin 13 was also taken off of the available pins as it was decided that it should be used as a status LED and should remain off if used. 

3/14 PCB Came in had issues. The Output enable pin was grounded not powered, which means it was disabled not enabled. (Woops) A small soldered wire fixed that. 
First Test : https://youtu.be/IeGvDfm8C_M

![photo of wire added to PCB](IMG_20210314_171215.jpg)


## Limitations
#### Files
   - Limited to a File Name of 8 Characters
     - example1.txt is at the max length
   - Is not case-sensitive 
     - example1.txt == EXAMPLE1.txt
      
#### Max SD card size is 32 GB
   - There are some potential work arounds for larger SD cards
   
#### LED Devices can only be added not removed per a given reboot
   - I really cant imagine this being an issue for anyone, but I thought its important to note just incase.
   - If 40 devices are created then they cannot be removed until a reboot
   - All 40 devices will be written to until a reboot occurs
   

## To Do
- [ ] Create Pattern Designer
- [ ] Loop Commands inside Files?
- [ ] Command Files for other Files?
- [ ] Allow devices to be removed without reboot?

