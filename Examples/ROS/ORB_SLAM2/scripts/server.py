#!/usr/bin/python3

import socket
import json

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('166.111.17.83',8008))
s.listen(5)
print('Waiting for connection...')
sock, addr = s.accept()
while 1:
    sock.settimeout(5)
    recvdata=sock.recv(4096)
    #if语句判断是否有数据或者数据是否有中断
    #防止出现json-nodata错误，导致server程序中断
    if len(recvdata) !=0:
        buf=json.loads(recvdata)
        print(buf)
        sock.send('yes i recv')
    else:
        print('pass')
        sock.send('out off client')
    #数据中断时进行服务重启程序，先close 再accept等待重新连线
    #可以防止出现当client意外终止导致server的中断（Broken pipe错误）
        sock.close()
        sock, addr = s.accept()
    #sock.send('yes')
sock.close()
