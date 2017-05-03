#!/usr/bin/env python
from flask import Flask, render_template, session, request
from flask_socketio import SocketIO, emit
import go
import gamemain

app = Flask(__name__, template_folder='./')
app.config['SECRET_KEY'] = 'secret!'

socketio = SocketIO(app)


@app.route('/')
def index():
    print('连接')
    return render_template('go.html')


@socketio.on('client_event')
def client_msg(msg):
    print('接受消息:', end='')
    print(msg)
    res = go.place(msg['data'])
    emit('server_response', {'data': res})
    # emit('server_response', {'data': msg['data']})


@socketio.on('connect_event')
def connected_msg(msg):
    print('连接')
    emit('server_response', {'data': msg['data']})


@socketio.on('game_start')
def game_start_msg(msg):
    print(msg)
    a = eval(msg['data'])
    if gamemain.is_exist_game(a):
        if gamemain.joingame(a):
            emit('game_start', {'user_id': a['user_id'], 'game_id': a['game_id'], 'begin': '1', 'side': 'white',\
                                'emeny': gamemain.get_emeny(a)}, broadcast=True)

            gamemain.create_sgf({'game_id':a['game_id'], 'PB': gamemain.get_emeny(a), 'PW':a['user_id']})
        else:
            emit('start_error',{'game_id': a['game_id']})
    else:
        gamemain.create_game(a)
        emit('game_start', {'user_id' : a['user_id'], 'game_id':a['game_id'], 'begin' : '0', 'side': 'black'},\
             broadcast=True)


@socketio.on('play_game_server')
def play_game_msg(msg):
    print(msg)
    a = eval(msg['data'])
    gamemain.writerecord(a)
    emit('play_game_client', {'data': tojson(a)}, broadcast=True)

@socketio.on('message')
def message(msg):
    a = eval(msg['data'])
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
