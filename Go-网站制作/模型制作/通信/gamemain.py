import os
import time

def create_game(game):
    f = open(game['game_id']+'.log', 'w')
    f.write('PB['+game['user_id']+']\n')
    f.close()


def joingame(game):
    f = open(game['game_id']+'.log', 'r')
    list = f.readlines()
    print(list, ' ', len(list))
    if len(list) == 1:
        f = open(game['game_id']+'.log', 'a')
        f.write('PW['+game['user_id']+']\n')
        f.close()
        return True
    else:
        f.close()
        return

def is_exist_game(game):
    filelist = [x for x in os.listdir('.') if os.path.isfile(x)]
    if game['game_id'] + '.log' in filelist:
        print('exist:'+ game['game_id'] + '.log')
        return True
    else:
        print('bot exist:'+ game['game_id'] + '.log')
        return False

def get_emeny(game):
    f = open(game['game_id']+'.log','r')
    line = f.readlines()
    return line[0][3:-2]

def writerecord(game):
    f = open('gamerecord/'+game['game_id']+'.sgf','a')
    f.write(';'+game['msg'])
    f.close()

def create_sgf(item):
    f =open('gamerecord/'+item['game_id']+'.sgf','w')
    f.write(';SZ[19]\nFF[3]\n')
    f.write('PB['+item['PB']+']\n')
    f.write('PW['+item['PW']+']\n')
    f.write('DT['+time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())+']\n')
    f.write('EV['+'棋局ID '+item['game_id']+']\n')
    f.close()

    pass
