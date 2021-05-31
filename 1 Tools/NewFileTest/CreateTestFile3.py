
f = open("frames9.txt", "wb")

Output = b''

f.write((4).to_bytes(1, byteorder='big')) # First Frame

for i in range(0, 10):
        f.write((3).to_bytes(1, byteorder='big')) # Create Device
        f.write((i).to_bytes(1, byteorder='big')) # Port
        f.write((9).to_bytes(1, byteorder='big')) # Number of LEDS

for iii in range(0, 255):
        for ii in range(0, 38):
                f.write((1).to_bytes(1, byteorder='big'))
                f.write((ii).to_bytes(1, byteorder='big'))
                for i in range(0, 9): # First Frame all White
                        f.write((iii).to_bytes(1, byteorder='big'))
                        f.write((255).to_bytes(1, byteorder='big'))
                        f.write((255).to_bytes(1, byteorder='big'))

        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame



f.close()
