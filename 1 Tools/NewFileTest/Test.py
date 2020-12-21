
f = open("bytes.txt", "wb")

Output = b''

for i in range(0, 256):
        f.write((i).to_bytes(1, byteorder='big'))

f.close()
