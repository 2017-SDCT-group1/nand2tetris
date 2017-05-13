import user
import os

filelist = [x for x in os.listdir('game_database/log') if os.path.isfile(x)]

print(filelist)
print(os.listdir('game_database/log'))
print(os.path())

user1 = {'user_id': 'bot1', 'password': '123456'}

user2 = {'user_id': 'bot2', 'password': '456456'}

user3 = {'user_id': 'bot2', 'password': '45646'}

if user.register(user1):
    print('注册成功')
else:
    print('注册失败')


if user.register(user2):
    print('注册成功')
else:
    print('注册失败')


if user.login(user3):
    print('登录成功')
else:
    print('登录失败')