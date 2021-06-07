import colorsys

f = open("wipe5.txt", "wb")

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

f.write((2).to_bytes(1, byteorder='big'))
f.write((125).to_bytes(2, byteorder='big'))

resolution = 15
for iii in range(0, resolution):
        for port in range(0, 12):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((port).to_bytes(1, byteorder='big'))
                if port == 0:
                        for ii in range(0, 28):
                                rgb = colorsys.hsv_to_rgb(iii/resolution, 1, 1)
                                f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))
                elif port == 11:
                        for ii in range(0, 8):
                                rgb = colorsys.hsv_to_rgb(iii/resolution, 1, 1)
                                f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))
                else:
                        for ii in range(0, 9):
                                rgb = colorsys.hsv_to_rgb(iii/resolution, 1, 1)
                                f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
                                f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))
                                        
                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        
f.close()
