from constant import *
import re
#注释
re_comment = re.compile(r'//[^\n]*\n|/\*(.*)?\*/', re.MULTILINE | re.DOTALL)
#标识符
re_id = r'[A-Za-z_][\w_]*'
#字符
re_symbol = '['+re.escape('{}[]().,;+-*/&|<>=')+']'
#字符串
re_string = r'"[^\n"]*"'
#整形常数
re_int_constant = r'\d+'
#keyword
re_keyword = '|'.join(keywords)
#word
re_word = re.compile(re_id+'|'+re_symbol+'|'+re_string+'|'+re_int_constant+'|'+re_keyword)

ERROR = -1

class JackTokenizer(object):
    def __init__(self, filename):
        try:
            self.f = open(filename, 'r')
            self.jack = self.f.read()
        except BaseException:
            print('Can\'t Open the Source File')


        #匹配的关键字列表
        self._WordList = self.remove_comment()


        #print(re.findall(re_word, self._WordList))
        #将关键词分开
        self._WordList = re.findall(re_word, self._WordList)


        print(self._WordList)
        #raise('1')
        #while self.hasMoreTokens():
        #    print(self.advance(), self.TokenType())
        self._cur_word_num = 0

    def remove_comment(self):
        return re_comment.sub('\n', self.jack)


    def hasMoreTokens(self):
        if len(self._WordList) > self._cur_word_num:
            return True
        else:
            return False

    def advance(self):
        if self.hasMoreTokens():
            self.cur_word = self._WordList[self._cur_word_num]
            self._cur_word_num += 1
            return self.cur_word
        else:
            print('No More WORD')
            return ERROR

    def TokenType(self, word):
        if re.match(re.compile(re_keyword), word):
            return KEYWORD
        elif re.match(re.compile(re_int_constant), word):
            return INT_CONST
        elif re.match(re.compile(re_string), word):
            return STRING_CONST
        elif re.match(re.compile(re_id), word):
            return IDENTIFIER
        elif re.match(re.compile(re_symbol), word):
            return SYMBOL

    def keyword(self, word):
        return keywords[word]

    def symbol(self):
        return self.cur_word

    def identifier(self):
        return self.cur_word

    def intVal(self, integer):
        return self.cur_word

    def stringVal(self, string):
        return self.cur_word.split('"')



    def get_target_word(self, wordtype):
        word = self._WordList[self._cur_word_num + 1]
        if self.TokenType(word) in wordtype:
            return word
        else:
            print('类型错误:期望的类型:')
            print(wordtype)
            print('实际类型:')
            print(self.TokenType(word))
            raise('ERROR')

