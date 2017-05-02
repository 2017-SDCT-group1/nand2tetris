#!/usr/bin/env python
from flask import Flask, render_template, session, request
from flask_socketio import SocketIO, emit
import go

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
    #emit('server_response', {'data': msg['data']})

@socketio.on('connect_event')
def connected_msg(msg):
    print('连接')
    emit('server_response', {'data': msg['data']})

if __name__ == '__main__':
    socketio.run(app, host='127.0.0.1')
