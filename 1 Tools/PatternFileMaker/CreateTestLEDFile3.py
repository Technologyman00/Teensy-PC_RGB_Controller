import colorsys
import random

f = open("rand4.txt", "wb")

Strip = 28*[3*[]]
Fans = 10*[9*[3*[]]]
Pump = 8*[3*[]]

f.write((3).to_bytes(1, byteorder='big')) # Create Strip Device
f.write((0).to_bytes(1, byteorder='big')) # Strip Port
f.write((28).to_bytes(1, byteorder='big')) # Strip Number of LEDS  

for i in range(1, 11):
        f.write((3).to_bytes(1, byteorder='big')) # Create Fan Device
        f.write((i).to_bytes(1, byteorder='big')) # Fan Port
        f.write((9).to_bytes(1, byteorder='big')) # Fan Number of LEDS

f.write((3).to_bytes(1, byteorder='big')) # Create Pump Device
f.write((11).to_bytes(1, byteorder='big')) # Pump Port
f.write((8).to_bytes(1, byteorder='big')) # Pump Number of LEDS


f.write((2).to_bytes(1, byteorder='big'))
f.write((250).to_bytes(2, byteorder='big'))

# rgb = colorsys.hsv_to_rgb(iii/resolution, 1, 1)

hue = 0
while hue < 360:
        for ii in range(0, 28):
                        rgb = colorsys.hsv_to_rgb(hue/360, 1, 1)
                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
                        hue = hue + 1

                        
        for c in range(0, 10):
                for ii in range(0, 9):
                        rgb = colorsys.hsv_to_rgb(hue/360, 1, 1)
                        Fans[c][ii][0] = rgb[0]
                        Fans[c][ii][1] = rgb[1]
                        Fans[c][ii][2] = rgb[2]
                        hue = hue + 1

        for ii in range(0, 8):
                        rgb = colorsys.hsv_to_rgb(hue/360, 1, 1)
                        Pump[ii][0] = rgb[0]
                        Pump[ii][1] = rgb[1]
                        Pump[ii][2] = rgb[2]
                        hue = hue + 1
                                        
        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

##for iii in range(0, 360):
##        f.write((0).to_bytes(1, byteorder='big'))
##        f.write((port).to_bytes(1, byteorder='big'))
##        if port == 0:
##                for ii in range(0, 28):
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##        elif port == 11:
##                for ii in range(0, 8):
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##        else:
##                for ii in range(0, 9):
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                        f.write((random.randint(0, 255)).to_bytes(1, byteorder='big'))
##                                
##f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        
f.close()
