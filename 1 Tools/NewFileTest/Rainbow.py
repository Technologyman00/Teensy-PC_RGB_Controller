import colorsys
import random
import math

f = open("corn21.txt", "wb")

f.write((3).to_bytes(1, byteorder='big')) # Create Device
f.write((0).to_bytes(1, byteorder='big')) # Port
f.write((28).to_bytes(1, byteorder='big')) # Number of LEDS  

for i in range(1, 11):
        f.write((3).to_bytes(1, byteorder='big')) # Create Device
        f.write((i).to_bytes(1, byteorder='big')) # Port
        f.write((9).to_bytes(1, byteorder='big')) # Number of LEDS

f.write((3).to_bytes(1, byteorder='big')) # Create Device
f.write((11).to_bytes(1, byteorder='big')) # Port
f.write((8).to_bytes(1, byteorder='big')) # Number of LEDS   

f.write((2).to_bytes(1, byteorder='big')) # Set Delay
f.write((11).to_bytes(2, byteorder='big')) # Delay time (ms)

startColor = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

multi = 65535
incr = 256
portincr = 50
gamma = 1.8

endreached = False
for iiii in range(0, 2560):
        #print(startColor)
        for port in range(0, 12):
                f.write((1).to_bytes(1, byteorder='big'))
                f.write((port).to_bytes(1, byteorder='big'))
                startColor[port] = startColor[port] + incr + (port*portincr)
                if port == 0:
                        for ii in range(0, 28):
                                        if((startColor[port] + ((ii*multi/28))) >= 65535):
                                                hue = (startColor[port] + ((ii*multi/28))) - math.floor((startColor[port] + ((ii*multi/28)))/65535)*65535
                                        else:
                                                hue = (startColor[port] + ((ii*multi/28)))

                                        hue = 65535*pow((hue/65535),gamma)

                                        f.write(int((hue)).to_bytes(2, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                elif port == 11:
                        for ii in range(0, 8):
                                        if((startColor[port] + ((ii*multi/8))) >= 65535):
                                                hue = (startColor[port] + ((ii*multi/8))) - math.floor((startColor[port] + ((ii*multi/8)))/65535)*65535
                                        else:
                                                hue = (startColor[port] + ((ii*multi/8)))

                                        hue = 65535*pow((hue/65535),gamma)
                                                
                                        f.write(int((hue)).to_bytes(2, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                else:
                        for ii in range(0, 9):
                                        if((startColor[port] + ((ii*multi/9))) >= 65535):
                                                hue = (startColor[port] + ((ii*multi/9))) - math.floor((startColor[port] + ((ii*multi/9)))/65535)*65535
                                        else:
                                                hue = (startColor[port] + ((ii*multi/9)))

                                        hue = 65535*pow((hue/65535),gamma)
                                                
                                        f.write(int((hue)).to_bytes(2, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        
        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        
f.close()
