import json


# 用户注册
# 返回true表示注册成功,false表示注册失败
# 注意:注册前必须要有该路径和数据文件，并且数据文件中必须要有一个初始用户
def register(user):

    user_db = open('user_database/user_list.db', 'r')
    user_list = json.loads(user_db.read())

    # 检验id是否存在
    for pre_user in user_list:
        if user['user_id'] == pre_user['user_id']:

            return False

    # 直接添加进数据库
    user_list.append(user)
    user_db.close()
    user_db = open('user_database/user_list.db', 'w')
    user_db.write(json.dumps(user_list))
    user_db.close()
    return True


def login(user):

    user_db = open('user_database/user_list.db', 'r')
    user_list = json.loads(user_db.read())
    user_db.close()
    # 检验id是否存在，并校验密码
    for pre_user in user_list:
        if user['user_id'] == pre_user['user_id']:
            if user['password'] == pre_user['password']:
                return True

    return False
