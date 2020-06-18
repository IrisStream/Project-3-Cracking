import random

name = input("Enter your name: ")

def shex(n):
    return "0x%X"%(n&0xffffffff)

serial = 0
for c in name:
    serial -= (ord(c) - 32)
print(shex(serial)[2:][::-1])

regFile = open("RES-REGGED.txt","w")
regFile.write(f"{random.randrange(1,5)}")
regFile.close()

regFile = open("RES-VALIDATE.diz","w")
regFile.close()