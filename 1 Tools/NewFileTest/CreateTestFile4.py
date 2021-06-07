
f = open("all7.txt", "wb")

Output = b''

#f.write((4).to_bytes(1, byteorder='big')) # First Frame

for iii in range(0, 13):
        f.write((3).to_bytes(1, byteorder='big')) # Create Device
        f.write((iii).to_bytes(1, byteorder='big')) # Port
        if iii == 0:
                f.write((28).to_bytes(1, byteorder='big')) # Number of LEDS
        else:
                f.write((9).to_bytes(1, byteorder='big')) # Number of LEDS
                

f.write((2).to_bytes(1, byteorder='big'))
f.write((100).to_bytes(2, byteorder='big'))

for iii in range(0, 13):
        if iii == 0:
                for ii in range(0, 28):
                        f.write((0).to_bytes(1, byteorder='big'))
                        f.write((iii).to_bytes(1, byteorder='big'))
                        for i in range(0, 28): # First Frame all White
                                if ii == i:                        
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
                        f.write((iii).to_bytes(1, byteorder='big'))
                        for i in range(0, 9): # First Frame all White
                                if ii == i:                        
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                        f.write((255).to_bytes(1, byteorder='big'))
                                else:
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))
                                        f.write((0).to_bytes(1, byteorder='big'))

                        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame



f.close()
