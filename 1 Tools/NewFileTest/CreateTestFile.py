
f = open("frames1.txt", "wb")

Output = b''

f.write((4).to_bytes(1, byteorder='big')) # First Frame

f.write((3).to_bytes(1, byteorder='big')) # Create Device
f.write((1).to_bytes(1, byteorder='big')) # Port
f.write((9).to_bytes(1, byteorder='big')) # Number of LEDS

f.write((0).to_bytes(1, byteorder='big'))
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))

f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

f.write((0).to_bytes(1, byteorder='big'))
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # Second Frame all Red
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))

f.write((4).to_bytes(1, byteorder='big')) # Start Third Frame

f.write((0).to_bytes(1, byteorder='big'))
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # Second Frame all Green
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))

f.write((4).to_bytes(1, byteorder='big')) # Start 4th Frame

f.write((0).to_bytes(1, byteorder='big'))
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # Second Frame all Green
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))



f.close()
