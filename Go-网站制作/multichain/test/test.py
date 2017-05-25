import os
import sys
from socket import *

default_remote_address =  '@192.168.1.108'
chain_unli_exe = 'multichain-util.exe'
chain_exe = 'multichaind.exe'
chain_cli_exe = 'multichain-cli.exe'

method_create = 'create'
CURRENT_CHAIN = 'chain'
method_run = '-daemon'
method_subscribe = 'subscribe'
method_list = 'liststreamitems'

authority_connect = 'connect'
authority_send = 'send'
authority_write = 'write'
authority_receive = 'receive'

chain_name = 'chainz'
port = '6747'
stream_name = 'streamz'

def main():
    
        connect_remote_chain()
        connect_stream()




def connect_remote_chain():
    #r = os.popen("multichaind.exe")
    fo = open("test.txt", "w+")
    print('正在连接远程区块链;')
    #name = input()
    #print('请输入连接端口号')
    #port = input()
    r = os.popen('%s %s%s:%s' % (chain_exe, chain_name, default_remote_address, port))
    p = r.read()
    q = p.split("\n")[4]
    fo.write(q)
    fo.close()
	
    
    
    print(q)
	
    send(q)
    print('here')
    os.popen('%s %s%s:%s' % (chain_exe, chain_name, default_remote_address, port))
    




def connect_stream():
    #print('请输入要区块链名:')
    #chain_name = 'chainz'
    print('正在连接到流;')
    #name = input()
    os.system('%s %s %s %s' % (chain_cli_exe, chain_name, method_subscribe, stream_name))
    

	
def send(q):

    host = "127.0.0.1" # set to IP address of target computer
    port = 13000
    addr = (host, port)
    UDPSock = socket(AF_INET, SOCK_DGRAM)
	
    data = input(q)
    UDPSock.sendto(data.encode('utf-8'), addr)
    UDPSock.close()
    #os._exit(0)
	
	
if __name__ == '__main__':
    main()
