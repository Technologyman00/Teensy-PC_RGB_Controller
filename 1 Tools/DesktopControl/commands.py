import serial
import colorsys
import time

arduino = serial.Serial('COM4', '115200')

def InitializeDevices(Ports, NumOfPixels):
    for i in range(0, len(Ports)):
        arduino.write((1).to_bytes(1, byteorder='big'))
        arduino.write((Ports[i]).to_bytes(1, byteorder='big') + (NumOfPixels[i]).to_bytes(1, byteorder='big'))
        

def SendRGBColors(Port, PixelColors):
    ByteColors = b''
    for i in range(0, len(PixelColors)):
        ByteColors = ByteColors + (PixelColors[i]).to_bytes(1, byteorder='big')

    arduino.write((2).to_bytes(1, byteorder='big'))    
    arduino.write((Port).to_bytes(1, byteorder='big'))
    arduino.write(ByteColors)
    arduino.flush()

def SendHSVColors(Port, PixelColors):
    ByteColors = b''
    for i in range(0, len(PixelColors), 3):
        RGBConverted = tuple(round(c * 255) for c in colorsys.hsv_to_rgb(PixelColors[i], PixelColors[i+1], PixelColors[i+2]))
        ByteColors = ByteColors + (RGBConverted[0]).to_bytes(1, byteorder='big') + (RGBConverted[1]).to_bytes(1, byteorder='big') + (RGBConverted[2]).to_bytes(1, byteorder='big')

    arduino.write((2).to_bytes(1, byteorder='big'))
    arduino.write((Port).to_bytes(1, byteorder='big'))
    arduino.write(ByteColors)
    arduino.flush()
    

def SendFrameData(Port, Frame, PixelColors):
    ByteColors = b''
    for i in range(0, len(PixelColors)):
        ByteColors = ByteColors + (PixelColors[i]).to_bytes(1, byteorder='big')

    arduino.write((3).to_bytes(1, byteorder='big'))
    arduino.write((Port).to_bytes(1, byteorder='big'))
    arduino.write((Frame).to_bytes(1, byteorder='big'))
    arduino.write(ByteColors)
    arduino.flush()


def StartFramePlay():
    arduino.write((4).to_bytes(1, byteorder='big'))

def StopFramePlay():
    arduino.write((255).to_bytes(1, byteorder='big'))
