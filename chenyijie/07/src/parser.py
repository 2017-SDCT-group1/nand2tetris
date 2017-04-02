#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re
from constant import *
class Parser(object):
    """docstring for ."""


    #_word = re.compile()
    def __init__(self, filename):
        f = open(filename, 'r')
        self._commands = f.readlines()#_commands是所有命令的list
        self._cur_command_line_num = 0#设置当前读取到的命令行数
        #print('init————ok')
        #print(len(self._commands))


        self._comment = re.compile('//.*$')#屏蔽注释的正则表达式
        _number = r'\d+'#匹配数字
        _id = r'[\w\-.]+'
        _word = re.compile(_number+'|'+_id)
        self._command_type = {'add':C_ARITHMETIC, 'sub':C_ARITHMETIC, 'neg':C_ARITHMETIC,
                        'eq' :C_ARITHMETIC, 'gt' :C_ARITHMETIC, 'lt' :C_ARITHMETIC,
                         'and':C_ARITHMETIC, 'or' :C_ARITHMETIC, 'not':C_ARITHMETIC,
                        'label':C_LABEL,    'goto':C_GOTO,      'if-goto':C_IF,
                        'push':C_PUSH,      'pop':C_POP,
                        'call':C_CALL,      'return':C_RETURN,  'function':C_FUNCTION}
    def hasMorecommands(self):
        if len(self._commands) > self._cur_command_line_num:
            return True
        else:
            return False

    def advance(self):
        self._cur_command = self._commands[self._cur_command_line_num]#设置当前读取到的命令
        self._cur_command_line_num = self._cur_command_line_num + 1
        self._cur_command = self._cur_command.strip('\n')
        self.no_comment_command = self._comment.sub(' ', self._cur_command)#去除注释

        if (self.no_comment_command != ' ') and (self.no_comment_command !=''):
            return self.no_comment_command
        else:
            return False

    def CommandType(self,str):
        _first_word = str.split(' ', 3)[0]
        if _first_word in self._command_type:
            return self._command_type[_first_word]
        else:
            return 'WRONG'

    def arg1(self):
        _second_word = self.no_comment_command.split(' ',3)[1]
        return _second_word

    def arg2(self):
        _third_word = self.no_comment_command.split(' ',3)[2]
        return _third_word



#file_name = input('Enter file name:\n')
#parser = Parser(file_name)
#while True:
#    if parser.hasMorecommands():
#        print (parser.advance())
#        print('-advance-')
#    else:
#        break
