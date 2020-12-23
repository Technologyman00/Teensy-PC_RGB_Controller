
f = open("test.txt", "wb")

Output = b''

f.write((0).to_bytes(1, byteorder='big')) # First Frame

f.close()
