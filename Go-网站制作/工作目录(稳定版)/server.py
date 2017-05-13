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
    return render_template('html/go.html')


@app.route('/register')
def register_html():
    print('注册')
    return render_template('html/register.html')


@app.route('/login')
def login_html():
    print('登录')
    return render_template('html/login.html')


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
    # 视为处理当前游戏
    cur_game = msg
    # 是否存在该对局
    if gamemain.is_exist_game(cur_game):
        # 如果存在

        # 判断是否可以加入
        if gamemain.joingame(cur_game):
            # 如果加入，返回消息(包括敌人消息)
            emit('game_start',
                 {'user_id': cur_game['user_id'], 'game_id': cur_game['game_id'], 'begin': '1', 'side': 'white', \
                  'emeny': gamemain.get_emeny(cur_game)}, broadcast=True)

            gamemain.create_sgf(
                {'game_id': cur_game['game_id'], 'PB': gamemain.get_emeny(cur_game), 'PW': cur_game['user_id']})
        else:

            # 否则报错
            emit('start_error', {'game_id': cur_game['game_id']})
    else:
        # 不存在该对局，那么就创建一个
        gamemain.create_game(cur_game)
        emit('game_start',
             {'user_id': cur_game['user_id'], 'game_id': cur_game['game_id'], 'begin': '0', 'side': 'black'}, \
             broadcast=True)


# 接受游戏落字消息
@socketio.on('play_game_server')
def play_game_msg(msg):
    print(msg)
    # 记录到sgf文件中
    gamemain.writerecord(msg)
    # 向其他连接的客户端广播
    emit('play_game_client', msg, broadcast=True)


# 处理用户发来的消息
@socketio.on('message')
def message(msg):
    # 直接向其他客户端广播
    emit('message', msg, broadcast=True)


# 处理注册
@socketio.on('register')
def register(msg):
    if gamemain.register(msg):
        emit('register_reply', {'data': 'success'})
    else:
        emit('register_reply', {'data': 'failed'})


# 处理登录
@socketio.on('login')
def login(msg):
    if gamemain.login(msg):
        emit('login_reply', {'data': 'success'})
    else:
        emit('login_reply', {'data': 'failed'})


# 将dict转化为字符串的json格式使其可以被javascript接收
def tojson(a):
    res = '['
    for x in a.keys():
        res += '[\'' + x + '\',\'' + str(a[x]) + '\']'
        res += ','
    res = res[0:-1]
    res += ']'
    return res


def log(msg):
    print(msg)


if __name__ == '__main__':
    socketio.run(app, host='127.0.0.1', port=8080)
