#!/usr/bin/env python
from flask import Flask, render_template, session, request
from flask_socketio import SocketIO, emit

import gamemain

app = Flask(__name__, template_folder='./')
app.config['SECRET_KEY'] = 'secret!'

socketio = SocketIO(app)


@app.route('/')
def index():
    print('连接')
# 返回网站主页
    return render_template('go.html')


# 以下是socketio接受到各个不同事件时的处理函数

# 测试遗留 忽略即可
@socketio.on('client_event')
def client_msg(msg):
    # print('接受消息:', end='')
    # print(msg)
    # res = go.place(msg['data'])
    # emit('server_response', {'data': res})
    # emit('server_response', {'data': msg['data']})
    pass

# 建立连接
@socketio.on('connect_event')
def connected_msg(msg):
    print('连接')
    emit('server_response', {'data': msg['data']})

# 游戏开始事件
@socketio.on('game_start')
def game_start_msg(msg):
    print(msg)
    a = eval(msg['data'])
    # 是否存在该对局
    if gamemain.is_exist_game(a):
        # 存在
        # 判断是否可以加入
        if gamemain.joingame(a):
            # 如果加入，返回消息
            emit('game_start', {'user_id': a['user_id'], 'game_id': a['game_id'], 'begin': '1', 'side': 'white',\
                                'emeny': gamemain.get_emeny(a)}, broadcast=True)

            gamemain.create_sgf({'game_id':a['game_id'], 'PB': gamemain.get_emeny(a), 'PW':a['user_id']})
        else:
            # 否则报错
            emit('start_error',{'game_id': a['game_id']})
    else:
        # 不存在该对局，那么就创建一个
        gamemain.create_game(a)
        emit('game_start', {'user_id' : a['user_id'], 'game_id':a['game_id'], 'begin' : '0', 'side': 'black'},\
             broadcast=True)

# 接受游戏落字消息
@socketio.on('play_game_server')
def play_game_msg(msg):
    print(msg)
    a = eval(msg['data'])
    # 记录到sgf文件中
    gamemain.writerecord(a)
    # 向其他连接的客户端广播
    emit('play_game_client', {'data': tojson(a)}, broadcast=True)

# 处理用户发来的消息
@socketio.on('message')
def message(msg):
    a = eval(msg['data'])
    # 直接向其他客户端广播
    emit('message', {'user_id': a['user_id'], 'game_id' : a['game_id'], 'message': a['message']}, broadcast=True)






# 将dict转化为字符串的json格式使其可以被javascript接收
def tojson(a):
    res = '['
    for x in a.keys():
        res += '[\''+x+'\',\''+str(a[x])+'\']'
        res += ','
    res = res[0:-1]
    res += ']'
    return res

def log(msg):
    print(msg)


if __name__ == '__main__':
    socketio.run(app, host='127.0.0.1')
