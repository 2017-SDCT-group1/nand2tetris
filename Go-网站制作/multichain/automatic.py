
import os

default_remote_address = '@115.159.180.193'

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


CURRENT_CHAIN = 'chain'
PORT = "6493"

def main():
    print('正在连接远程区块链')
    connect_remote_chain()
    print('正在查看流上的信息')
    connect_stream()

def connect_remote_chain():
    os.system('%s %s%s:%s' % (chain_exe, CURRENT_CHAIN, default_remote_address, PORT))
    print('没有连接到远程服务器的权限!')
    print('请保存上述密钥,按照说明进行添加!')

def connect_stream():
    os.system('%s %s %s %s' % (chain_cli_exe, CURRENT_CHAIN, method_subscribe, PORT))
    print("设置完成")
    os.system("pause")

if __name__ == '__main__':
    main()
