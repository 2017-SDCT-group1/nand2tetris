import os

default_remote_address = '@115.159.180.193'

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


def main():
    print('请输入选项表明接下来的操作')
    print('[1]:创建区块链')
    print('[2]:关闭区块链')
    print('[3]:开始运行区块链')
    print('[4]:添加权限')
    print('[5]:连接远程区块链')
    print('[6]:创建流')
    print('[7]:发布信息')
    print('[8]:连接到流上')
    print('[9]:查看流上的信息')

    option = input()
    if option == '1':
        create_chain()
    if option == '2':
        pass
    if option == '3':
        run_chain()
    if option == '4':
        add_node_authority()
    if option == '5':
        connect_remote_chain()
    if option == '6':
        create_stream()
    if option == '7':
        publish_stream()
    if option == '8':
        connect_stream()
    if option == '9':
        get_data_stream()


def create_chain():
    print('请输入要创建的区块链名:')
    name = input()
    output = os.popen('%s %s %s' % (chain_unli_exe, method_create, name))
    CURRENT_CHAIN = name
    print(output.read())
    if 'successfully' in output.read():
        print('创建区块链成功')
    else:
        print('创建区块链失败')
    main()


def run_chain():
    print('请输入要运行的区块链名:(直接回车代表当前区块链)')
    print('请保持此程序运行')
    name = input()
    if name == '':
        if CURRENT_CHAIN != 'chain':
            os.system('%s %s %s' % (chain_exe, CURRENT_CHAIN, method_run))
    else:
        os.system('%s %s %s' % (chain_exe, name, method_run))
    print('您尝试运行的区块链不是您本地创建的！')
    print('没有连接到远程服务器的权限!')
    print('请保存上述密钥,按照说明进行添加!')
    main()


def add_node_authority():
    print('输入要添加的密钥到key.txt中(一个一行)，接下来将赋予其connect与receive权限:')
    print('请输入要添加权限的区块链名称:')
    name = input()
    f = open('key.txt', 'r')
    keys = f.readlines()
    for key in keys:
        os.system('%s %s grant %s %s' % (chain_cli_exe, name, key, authority_connect))
        os.system('%s %s grant %s %s' % (chain_cli_exe, name, key, authority_receive))

    main()


def connect_remote_chain():
    print('请输入要连接的区块链名:')
    name = input()
    print('请输入连接端口号')
    port = input()
    os.system('%s %s%s:%s' % (chain_exe, name, default_remote_address, port))
    print('没有连接到远程服务器的权限!')
    print('请保存上述密钥,按照说明进行添加!')
    main()


def create_stream():
    print('请输入要连接的区块链名:')
    chain_name = input()
    print('输入要创建的stream名:')
    name = input()
    os.system('multichain-cli.exe %s %s %s %s %s' % (chain_name, method_create, 'stream', name, 'false'))
    main()


def publish_stream():
    print('请输入要连接的区块链名:')
    chain_name = input()
    print('输入用来发布的stream名:')
    name = input()
    print('输入发布信息:(hex)')
    content = input()
    print('输入使用的key:')
    key = input()
    os.system('multichain-cli.exe %s %s %s %s %s' % (chain_name, 'publish', name, key, content))
    main()


def connect_stream():
    print('请输入要区块链名:')
    chain_name = input()
    print('输入stream名:')
    name = input()
    os.system('%s %s %s %s' % (chain_cli_exe, chain_name, method_subscribe, name))
    main()


def get_data_stream():
    print('请输入要区块链名:')
    chain_name = input()
    print('输入stream名:')
    name = input()
    os.system('%s %s %s %s' % (chain_cli_exe, chain_name, method_list, name))
    main()


if __name__ == '__main__':
    main()
