
f = open("fan.txt", "wb")

Output = b''

f.write((4).to_bytes(1, byteorder='big')) # First Frame

f.write((3).to_bytes(1, byteorder='big')) # Create Device
f.write((1).to_bytes(1, byteorder='big')) # Port
f.write((9).to_bytes(9, byteorder='big')) # Number of LEDS

f.write((2).to_bytes(1, byteorder='big'))
f.write((10).to_bytes(2, byteorder='big'))

for ii in range(0,9):
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((1).to_bytes(1, byteorder='big'))
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
