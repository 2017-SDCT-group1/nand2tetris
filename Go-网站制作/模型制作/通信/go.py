string = 'abcdefghijklmnoprstuvwxyz'


def place(str):
    x = string.index(str[2])+1
    y = string.index(str[3])+1

    r_x = 20 - x
    r_y = 20 - y
    print('before', x,' ' , y,'after',r_x,' ',r_y)
    print('W['+string[r_x-1]+string[r_y-1]+']')
    return 'W['+string[r_x-1]+string[r_y-1]+']'