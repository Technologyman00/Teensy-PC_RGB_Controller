import colorsys

f = open("fron15.txt", "wb")

for i in range(0, 12):
        f.write((3).to_bytes(1, byteorder='big')) # Create Device
        f.write((i).to_bytes(1, byteorder='big')) # Port
        f.write((28).to_bytes(1, byteorder='big')) # Number of LEDS     

f.write((2).to_bytes(1, byteorder='big'))
f.write((30).to_bytes(2, byteorder='big'))

resolution = 360
for iii in range(0, resolution):
        for port in range(0, 12):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((port).to_bytes(1, byteorder='big'))
                for ii in range(0, 28):
                        if(ii == 0):
                                rgb = colorsys.hsv_to_rgb(iii/resolution, 1, 1)
                                f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))
                        else:
                                rgb = colorsys.hsv_to_rgb((iii+(ii*6))/resolution, 1, 1)
                                f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))
                                        
        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        
f.close()
