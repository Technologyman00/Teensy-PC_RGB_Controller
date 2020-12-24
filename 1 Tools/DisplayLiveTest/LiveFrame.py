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

f.write(b'X')

print("Frame 2")
f.write(b's ')
f.write(b'R')
f.write((1).to_bytes(1, byteorder='big'))
for i in range(0, 9): # First Frame all White
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))
        f.write((0).to_bytes(1, byteorder='big'))

time.sleep(10)

f.write(b'X')

print("Finished.")

while True:
        print(f.read())
        
f.close()
