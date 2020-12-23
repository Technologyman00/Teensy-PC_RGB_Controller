import serial
import time

f = serial.Serial('COM4', '9600')

f.reset_input_buffer()
a = 10
print((a).to_bytes(4, byteorder='big'))
f.write((a).to_bytes(4, byteorder='big'))
print(f.read(2))
