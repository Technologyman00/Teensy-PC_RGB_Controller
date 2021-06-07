
f = open("all8.txt", "wb")

Output = b''

f.write((4).to_bytes(1, byteorder='big')) # First Frame

for i in range(0, 12):
        f.write((3).to_bytes(1, byteorder='big')) # Create Device
        f.write((i).to_bytes(1, byteorder='big')) # Port
        if (i == 0):
                f.write((30).to_bytes(9, byteorder='big')) # Number of LEDS
        if (i == 11):
                f.write((8).to_bytes(9, byteorder='big')) # Number of LEDS
        else:
                f.write((9).to_bytes(9, byteorder='big')) # Number of LEDS

f.write((2).to_bytes(1, byteorder='big'))
f.write((150).to_bytes(2, byteorder='big'))

for i in range(0, 12):
        if i == 0:
                for ii in range(0, 30):
                        f.write((0).to_bytes(1, byteorder='big'))
                        f.write((i).to_bytes(1, byteorder='big'))
                        for iii in range(0, 30):
                                if ii == iii:
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                else:        
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))

                        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        if i == 11:
                for ii in range(0, 8):
                        f.write((0).to_bytes(1, byteorder='big'))
                        f.write((i).to_bytes(1, byteorder='big'))
                        for iii in range(0, 8):
                                if ii == iii:
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                else:        
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))

                        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        else:
                for ii in range(0, 9):
                        f.write((0).to_bytes(1, byteorder='big'))
                        f.write((i).to_bytes(1, byteorder='big'))
                        for iii in range(0, 9):
                                if ii == iii:
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                else:        
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))

                        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame



f.close()
