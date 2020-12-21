from smbus2 import SMBus

# Open i2c bus 1 and read one byte from address 80, offset 0
bus = SMBus(1)
b = bus.read_byte_data(80, 0)
print(b)
bus.close()

def fcntl(fd, op, arg=0):
    return 0

def ioctl(fd, op, arg=0, mutable_flag=True):
    if mutable_flag:
        return 0
    else:
        return ""

def flock(fd, op):
    return

def lockf(fd, operation, length=0, start=0, whence=0):
    return
