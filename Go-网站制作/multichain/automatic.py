
#需要改的地方
#第一处port chain_name和stream
#第二处函数upload




import os
import socket
import json


chain_unli_exe = 'multichain-util.exe'
chain_exe = 'multichaind.exe'
chain_cli_exe = 'multichain-cli.exe'

method_create = 'create'

method_run = '-daemon'
method_subscribe = 'subscribe'
method_list = 'liststreamitems'

authority_connect = 'connect'
authority_send = 'send'
authority_write = 'write'
authority_receive = 'receive'


#1
default_remote_address = '@115.159.180.193'
CURRENT_CHAIN = 'chain'
PORT = "4759"
STREAM = "test"
#1


def main():
    print('正在连接远程区块链')
    connect_remote_chain()
    print('正在查看流上的信息')
    connect_stream()


def connect_remote_chain():
    os.system('%s %s%s:%s' % (chain_exe, CURRENT_CHAIN, default_remote_address, PORT))
    result = os.popen('%s %s%s:%s' % (chain_exe, CURRENT_CHAIN, default_remote_address, PORT)).read()
    key = result.split('\n')[4]
    print(key)
    os.system("pause")
    #获取key
    upload(key)

    #上传
    os.system('%s %s %s' % (chain_exe, CURRENT_CHAIN, method_run))
    system("pause")

#2
def unload(key):
    pass
#2


def connect_stream():
    os.system('%s %s %s %s' % (chain_cli_exe, CURRENT_CHAIN, method_subscribe, STREAM))
    print("设置完成")
    os.system("pause")

if __name__ == '__main__':
    main()
