#!/usr/bin/python

import time
import socket
import json
import random

HOST='166.111.17.83'
PORT=8008
BUFFER=4096

soc=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
soc.connect((HOST,PORT))
while 1:
    time.sleep(0.1)
    m0=random.randint(0,25)
    m1=random.randint(0,25)
    m2=random.randint(0,25)
    m3=random.randint(0,55)
    m4=random.randint(0,55)
    m5=random.randint(0,55)
    m6=random.randint(0,255)
    m7=random.randint(0,255)
    m8=random.randint(0,255)
    m9=random.randint(0,255)
    mess=[m0,m1,m2,m3,m4,m5,m6,m7,m8,m9]
    #soc.send(json.dumps(mess))
    soc.send(str(mess))
    buf=soc.recv(BUFFER)
    print(buf)
soc.close()
