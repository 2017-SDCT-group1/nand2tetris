import os
import sys
import socket
import time

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

chain_name = 'g'
port = '4289'
stream_name = 'h'
default_remote_address = '@192.168.1.105'
host = '192.168.1.105'
# host = "127.0.0.1" # set to IP address of target computer
host_port = 9999
buffer = 4096


def main():
    connect_remote_chain()
    connect_stream()



def connect_remote_chain():
    # r = os.popen("multichaind.exe")
    fo = open("test.txt", "w+")
    print('正在连接远程区块链;')
    # name = input()
    # print('请输入连接端口号')
    # port = input()
    r = os.popen('%s %s%s:%s' % (chain_exe, chain_name, default_remote_address, port))
    p = r.read()
    q = p.split("\n")[4]
    fo.write(q)
    fo.close()

    print(q)
    send(q)
    #print('here')
    os.popen('%s %s%s:%s' % (chain_exe, chain_name, default_remote_address, port))
    os.system("pause")


def connect_stream():
    print('正在连接到流;')
    os.system('%s %s %s %s' % (chain_cli_exe, chain_name, method_subscribe, stream_name))


def send(q):
    global host
    global host_port
    global buffer
    # while True:
    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soc.connect((host, host_port))

    time.sleep(1)

    soc.send(q.encode('utf-8'))
    buf = soc.recv(buffer)
    print(buf)
    soc.close()


if __name__ == '__main__':
    main()
