import serial
import time

f = serial.Serial('COM4', '9600')

print("Sending Frame...")
print("Frame 1")

f.write(b's ')
f.write(b'R')
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))

time.sleep(10)

print("Frame 2")
f.write(b'R')
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))

time.sleep(10)

print("Frame 3")
f.write(b'H')
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((90).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))

time.sleep(10)

print("Frame 4")
f.write(b'R')
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))

time.sleep(10)

print("Frame 5")
f.write(b'H')
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((180).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))
        f.write((255).to_bytes(1, byteorder='big'))

time.sleep(10)



f.write(b'X')

print("Finished.")
        
f.close()
