#-*- coding: utf-8 -*-

name = "testpic."
file = open(name + "png", "rb")
res = open(name + "txt", "w")
s = ''

for i in bytearray(file.read()):
    t = str(format(i, '02x'))
    s += str(bin(int(t, 16))[2:])
    if len(s) < 8:
        s = '0'*(8 - len(s)) + s

print(s)

res.write(s)
file.close()
res.close()
