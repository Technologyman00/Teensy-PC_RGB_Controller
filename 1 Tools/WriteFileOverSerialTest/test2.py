import serial

f = serial.Serial('COM4', '9600')

f.write(b'p frames4.txt')

