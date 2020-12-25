# Teensy-PC_RGB_Controller
 
The whole Idea behind this project was to create a much better RGB controller than the controllers I currently have or many of the MB softwares I have seen. Currently It has already met that goal as it can play any pattern for many many LEDs and up to 40 devices. I am still working on the user interface and many quality of life things, but the main functionality does work. HOWEVER, it will need a PCB made inorder to power all the LEDs as a Teensy cannot power that many safely.

## Downsides
1. Files
    - Limited to a File Name of 8 Characters
      - example1.txt is at the max length
    - Is not case-sensitive 
      - example1.txt == EXAMPLE1.txt
      
2. Max SD card size is 32 GB
   - There are some potential work arounds for larger SD cards
   
3. LED Devices can only be added not removed per a given reboot
   - I really cant imagine this being an issue for anyone, but I thought its important to note just incase.
   - If 40 devices are created then they cannot be removed until a reboot
   - All 40 devices will be written to until a reboot occurs
   

## To Do
- [x] Add File Sending over USB
- [x] Transfer to VSCode
- [x] Create Multiple Code Files
- [x] Add Live Frame Sending over USB
- [x] Improve Live Frame Sending
- [ ] Clean Up Code for Default File Reading
- [ ] Continue Work on Windows App for Sending File


