import time
import commands

#https://pypi.org/project/smbus2/

wait = 0.0001

time.sleep(0.5)
commands.InitializeDevices([3], [9])

print("Devices Initalized")

time.sleep(wait)

increase = 20

print("Starting Color Sending")

if False:
    while True:
        
        for c in range(0, 360, 1):
            ColorData = [c/360, 1, 1, (c + ((1*360)/9))/360, 1, 1, (c+((2*360)/9))/360, 1, 1, (c+((3*360)/9))/360, 1, 1, (c+((4*360)/9))/360, 1, 1, (c+((5*360)/9))/360, 1, 1, (c+((6*360)/9))/360, 1, 1, (c+((7*360)/9))/360, 1, 1, (c+((8*360)/9))/360, 1, 1]
                    
            commands.SendHSVColors(3, ColorData)
            #time.sleep(0.1)

    
if True:
    ColorData = [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0]
    commands.SendFrameData(3, 0, ColorData)

    ColorData = [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0]
    commands.SendFrameData(3, 1, ColorData)

    print("Starting Frame Play")

    commands.StartFramePlay()


    time.sleep(60)

    print("Stopping Frame Play")

    commands.StopFramePlay()

