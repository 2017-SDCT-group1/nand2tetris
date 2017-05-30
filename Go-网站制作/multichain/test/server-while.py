import socket
import sys
import os

chain_unli_exe = 'multichain-util.exe'
chain_exe = 'multichaind.exe'
chain_cli_exe = 'multichain-cli.exe'

authority_connect = 'connect'
authority_send = 'send'
authority_write = 'write'
authority_receive = 'receive'

name = 'a'

serversocket = socket.socket(
		socket.AF_INET, socket.SOCK_STREAM)
		
host = '192.168.1.105'

port = 9999

serversocket.bind((host, port))

serversocket.listen(5)
print('here')

clientsocket,addr = serversocket.accept()
print('链接地址:%s' % str(addr))




text = clientsocket.recv(1024)

text = text.decode('utf-8')
print(text)


os.system('%s ' % ( text))


msg = 'test'

clientsocket.send(msg.encode('utf-8'))

clientsocket.close()