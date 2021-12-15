import colorsys

f = open("cyc99.txt", "wb")

Strip = 28*[[0, 0, 0]]
##Fans = 11*[9*[[0, 0, 0]]]
##Fans = [[[0 for k in range(3)] for j in range(9)] for i in range(11)]


Fan1 = 9*[[0, 0, 0]]
Fan2 = 9*[[0, 0, 0]]
Fan3 = 9*[[0, 0, 0]]
Fan4 = 9*[[0, 0, 0]]
Fan5 = 9*[[0, 0, 0]]
Fan6 = 9*[[0, 0, 0]]
Fan7 = 9*[[0, 0, 0]]
Fan8 = 9*[[0, 0, 0]]
Fan9 = 9*[[0, 0, 0]]
Fan10 = 9*[[0, 0, 0]]

Pump = 8*[[0, 0, 0]]

f.write((3).to_bytes(1, byteorder='big')) # Create Strip Device
f.write((0).to_bytes(1, byteorder='big')) # Strip Port
f.write((28).to_bytes(1, byteorder='big')) # Strip Number of LEDS  

for i in range(1, 11):
        f.write((3).to_bytes(1, byteorder='big')) # Create Fan Device
        f.write((i).to_bytes(1, byteorder='big')) # Fan Port
        f.write((9).to_bytes(1, byteorder='big')) # Fan Number of LEDS

f.write((3).to_bytes(1, byteorder='big')) # Create Pump Device
f.write((11).to_bytes(1, byteorder='big')) # Pump Port
f.write((8).to_bytes(1, byteorder='big')) # Pump Number of LEDS


f.write((2).to_bytes(1, byteorder='big'))
f.write((100).to_bytes(2, byteorder='big'))

# rgb = colorsys.hsv_to_rgb(iii/resolution, 1, 1)

hue = 0
incra = 5
res = 360*3
for frames in range(0, 100):
        for ii in range(0, 28):
                        f.write((0).to_bytes(1, byteorder='big'))
                        f.write((0).to_bytes(1, byteorder='big'))
                                
                        rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                        Strip[ii] =[int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]


                        for post in range(0, 28):
                                f.write((Strip[post][0]).to_bytes(1, byteorder='big'))
                                f.write((Strip[post][1]).to_bytes(1, byteorder='big'))
                                f.write((Strip[post][2]).to_bytes(1, byteorder='big'))
                        
                        hue = hue + incra

                        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        
        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((1).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan1[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan1[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan1[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan1[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((2).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan2[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan2[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan2[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan2[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((3).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan3[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan3[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan3[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan3[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((4).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan4[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan4[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan4[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan4[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((5).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan5[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan5[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan5[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan5[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((6).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan6[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan6[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan6[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan6[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((7).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan7[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan7[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan7[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan7[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame


        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((8).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan8[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan8[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan8[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan8[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame


        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((9).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan9[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan9[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan9[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan9[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame

        for ii in range(0, 9):
                f.write((0).to_bytes(1, byteorder='big'))
                f.write((10).to_bytes(1, byteorder='big'))

                rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                Fan10[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]
            
                for post in range(0, 9):
                        f.write((Fan10[post][0]).to_bytes(1, byteorder='big'))
                        f.write((Fan10[post][1]).to_bytes(1, byteorder='big'))
                        f.write((Fan10[post][2]).to_bytes(1, byteorder='big'))
                        
                hue = hue + incra

                f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
                
        for ii in range(0, 8):
                        f.write((0).to_bytes(1, byteorder='big'))
                        f.write((11).to_bytes(1, byteorder='big'))
                        
                        rgb = colorsys.hls_to_rgb(hue/res, 0.5, 1)
##                        f.write((int(255*rgb[0])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[1])).to_bytes(1, byteorder='big'))
##                        f.write((int(255*rgb[2])).to_bytes(1, byteorder='big'))

                        Pump[ii] = [int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])]

                        for post in range(0, 8):
                                f.write((Pump[post][0]).to_bytes(1, byteorder='big'))
                                f.write((Pump[post][1]).to_bytes(1, byteorder='big'))
                                f.write((Pump[post][2]).to_bytes(1, byteorder='big'))
                        
                        hue = hue + incra
                        
                        f.write((4).to_bytes(1, byteorder='big')) # Start Second Frame
        
f.close()
