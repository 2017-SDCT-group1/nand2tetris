from constant import *
import JackTokenizer

class CompilationEngine(object):
    def __init__(self, filename):

        self.filename = filename.split('.', 2)[0]
        self.jacktoken = JackTokenizer.JackTokenizer(filename)
        self.wordlist = self.jacktoken._WordList

        try:
            print('Outfile:'+filename.split('.', 2)[0]+'.xml')
            self.outfile = open(filename.split('.', 2)[0] + '.xml', 'w')
        except BaseException:
            print('Can\'t Open XML File')

        #self.XMLT()
        self.CompilerClass()

    def log(self, msg):
        print(msg)



    def XMLT(self):
        f = open(self.filename+'T.xml','w')
        f.write('<token>\n')
        for n in self.jacktoken._WordList:
            print(n)
            self.jacktoken.advance()
            if self.jacktoken.TokenType(n) == KEYWORD:
                f.write('<keyword>'+n+'</keyword>\n')
            elif self.jacktoken.TokenType(n) == STRING_CONST:
                f.write('<stringConstant>'+n.strip('"')+'</stringConstant>\n')
            elif self.jacktoken.TokenType(n) == IDENTIFIER:
                f.write('<identifier>'+n+'</identifier>\n')
            elif self.jacktoken.TokenType(n) == INT_CONST:
                f.write('<integerConstant>'+n+'</integerConstant>\n')
            elif self.jacktoken.TokenType(n) == SYMBOL:
                f.write('<symbol>'+n+'</symbol>\n')

        f.write('</token>\n')
        f.close()




    def CompilerClass(self):
        self.xml_begin('class')
        if self.get_now_required_type_word(KEYWORD, CLASS):
            self.xml_keyword(self.jacktoken.advance())
        else:
            raise(TypeError)

        if self.get_now_required_type_word(IDENTIFIER):
            self.xml_id(self.jacktoken.advance())
        else:
            raise (TypeError)

        #self.xml_symbol(self.get_required_symbol('{'))
        self.xml_symbol(self.jacktoken.advance())

        while self.is_ClassVarDec():
            self.CompilerClassVarDec()

        while self.is_subroutineDec():
            self.CompilerSubroutie()

        #self.xml_symbol(self.get_required_symbol('}'))
        self.xml_symbol(self.jacktoken.advance())
        self.xml_end('class')



    def CompilerClassVarDec(self):
        self.xml_begin('ClassVarDec')
        self.xml_keyword(self.jacktoken.advance())

        #type
        if self.get_now_required_type_word(KEYWORD, CHAR) or self.get_now_required_type_word(KEYWORD, INT) or \
        self.get_now_required_type_word(KEYWORD, BOOLEAN):
            self.xml_keyword(self.jacktoken.advance())
        else:
            self.xml_id(self.jacktoken.advance())

        while self.get_next_word() != ';':
            if self.get_next_word_type() == IDENTIFIER:
                self.xml_id(self.jacktoken.advance())
            elif self.get_next_word_type() == SYMBOL:
                self.xml_symbol(self.jacktoken.advance())
        #';'
        self.xml_symbol(self.jacktoken.advance())

        self.xml_end('ClassVarDec')


    def CompilerSubroutie(self):
        self.xml_begin('subroutineDec')

        # constructor methord function
        self.xml_keyword(self.jacktoken.advance())

        #type
        if self.get_now_required_type_word(KEYWORD, CHAR) or self.get_now_required_type_word(KEYWORD, INT) or \
        self.get_now_required_type_word(KEYWORD, BOOLEAN) or self.get_now_required_type_word(KEYWORD, VOID):
            self.xml_keyword(self.jacktoken.advance())
        else:
            self.xml_id(self.jacktoken.advance())

        #name
        if self.get_now_required_type_word(IDENTIFIER):
            self.xml_id(self.jacktoken.advance())

        #'('
        if self.get_next_word_type() == SYMBOL:
            self.xml_symbol(self.jacktoken.advance())

        self.CompilerParameterList()


        #')'
        if self.get_next_word_type() == SYMBOL:
            self.xml_symbol(self.jacktoken.advance())


        self.CompilerSubroutieBody()


        self.xml_end('subroutineDec')


    def CompilerParameterList(self):
        self.xml_begin('parameterList')
        while self.get_next_word() != ')':
            if self.get_now_required_type_word(KEYWORD, CHAR) or self.get_now_required_type_word(KEYWORD, INT) or self.get_now_required_type_word(KEYWORD, BOOLEAN):
                self.xml_keyword(self.jacktoken.advance())
            elif self.get_now_required_type_word(SYMBOL):
                self.xml_symbol(self.jacktoken.advance())
            elif self.get_now_required_type_word(IDENTIFIER):
                self.xml_id(self.jacktoken.advance())
        self.xml_end('parameterList')

    def CompilerSubroutieBody(self):
        self.xml_begin('subroutieBody')
        # '{'
        if self.get_next_word_type() == SYMBOL:
            self.xml_symbol(self.jacktoken.advance())

        while self.is_VarDec():
            self.CompilerVarDec()

        while self.is_statement():
            self.CompilerStatements()

            # '}'
            if self.get_next_word_type() == SYMBOL:
                self.xml_symbol(self.jacktoken.advance())
        self.xml_end('subroutieBody')



    def CompilerVarDec(self):
        self.xml_begin('VarDec')
        self.xml_keyword(self.jacktoken.advance())#var

        #type
        if self.get_now_required_type_word(KEYWORD, CHAR) or self.get_now_required_type_word(KEYWORD, INT) or \
        self.get_now_required_type_word(KEYWORD, BOOLEAN):
            self.xml_keyword(self.jacktoken.advance())
        else:
            self.xml_id(self.jacktoken.advance())

        while self.get_next_word() != ';':
            if self.get_next_word_type() == IDENTIFIER:
                self.xml_id(self.jacktoken.advance())
            elif self.get_next_word_type() == SYMBOL:
                self.xml_symbol(self.jacktoken.advance())

        # ';'
        self.xml_symbol(self.jacktoken.advance())
        self.xml_end('VarDec')


    def CompilerStatements(self):
        if self.is_statement() == LET:
            self.CompilerLet()
        if self.is_statement() == DO:
            self.CompilerDo()
        if self.is_statement() == WHILE:
            self.CompilerWhile()
        if self.is_statement() == RETURN:
            self.CompilerReturn()
        if self.is_statement() == IF:
            self.CompilerIf()


    def CompilerDo(self):
        self.xml_begin('doStatement')
        # do
        self.xml_keyword(self.jacktoken.advance())

        self.CompilersubroutineCall()

        #;
        self.xml_symbol(self.jacktoken.advance())
        self.xml_end('doStatement')


    def CompilerReturn(self):
        self.xml_begin('returnStatement')
        # return
        self.xml_keyword(self.jacktoken.advance())

        if self.get_next_word() == ';':
            self.xml_symbol(self.jacktoken.advance())
        else:
            self.CompilerExpression()
            self.xml_symbol(self.jacktoken.advance())

        self.xml_end('returnStatement')

    def CompilerIf(self):
        self.xml_begin('ifStatement')
        # if
        self.xml_keyword(self.jacktoken.advance())
        # (
        self.xml_symbol(self.jacktoken.advance())

        self.CompilerExpression()

        # )
        self.xml_symbol(self.jacktoken.advance())

        #{
        self.xml_symbol(self.jacktoken.advance())

        while self.is_statement():
            self.CompilerStatements()

        #}
        self.xml_symbol(self.jacktoken.advance())


        if self.get_next_word() == 'else':

            # else
            self.xml_keyword(self.jacktoken.advance())

            # {
            self.xml_symbol(self.jacktoken.advance())

            while self.is_statement():
                self.CompilerStatements()

            # }
            self.xml_symbol(self.jacktoken.advance())


        self.xml_end('ifStatement')

    def CompilerLet(self):
        self.xml_begin('letStatement')
        self.xml_keyword(self.jacktoken.advance())#let

        if self.get_now_required_type_word(IDENTIFIER):
            self.xml_id(self.jacktoken.advance())#id

        if self.get_next_word() == '[':
            self.xml_symbol(self.jacktoken.advance())#'['
            self.CompilerExpression()
            self.xml_symbol(self.jacktoken.advance())#']'

        self.xml_symbol(self.jacktoken.advance())#'='

        self.CompilerExpression()

        self.xml_symbol(self.jacktoken.advance())#';'

        self.xml_end('letStatement')

    def CompilerWhile(self):
        self.xml_begin('whileStatement')
        # while
        self.xml_keyword(self.jacktoken.advance())

        # (
        self.xml_symbol(self.jacktoken.advance())

        self.CompilerExpression()

        # )
        self.xml_symbol(self.jacktoken.advance())

        #{
        self.xml_symbol(self.jacktoken.advance())

        while self.is_statement():
            self.CompilerStatements()

        #}
        self.xml_symbol(self.jacktoken.advance())

        self.xml_end('whileStatement')

    def CompilerExpression(self):
        self.xml_begin('expression')
        self.CompilerTerm()
        self.log('表达式的下一个字符'+ self.get_next_word())
        while self.get_next_word() in op:
            self.xml_symbol(self.jacktoken.advance())#'op'
            self.CompilerTerm()
        self.xml_end('expression')

    def CompilerTerm(self):
        self.xml_begin('term')
        self.log('当前命令:'+ self.get_next_word())
        self.log('新的一层term')
        #数值常量
        if self.get_next_word_type() == INT_CONST:
            self.log('数值常量')
            self.xml_int(self.jacktoken.advance())
        #字符串常量
        elif self.get_next_word_type() == STRING_CONST:
            self.log('字符串常量')
            self.xml_str(self.jacktoken.advance())
        #keyword
        elif self.get_next_word() in keywordconstant:
            self.log('keywordconstant')
            self.xml_keyword(self.jacktoken.advance())
        #出现ID 有几种情况
        elif self.get_next_word_type() == IDENTIFIER:
            self.log('//出现ID')
            '''#出现下面标志说明表达式结束
            if self.get_next_two_word() == ')' or self.get_next_two_word() == ']' or self.get_next_two_word() == ';' or \
                            self.get_next_two_word() == ',':'''

            #出现[说明是数组
            if self.get_next_two_word() == '[':
                self.log('//数组')
                #id
                self.xml_id(self.jacktoken.advance())
                #[
                self.xml_symbol(self.jacktoken.advance())

                self.CompilerExpression()

                #]
                self.xml_symbol(self.jacktoken.advance())
            #出现(或者.说明是调用其他函数
            elif self.get_next_two_word() == '(' or self.get_next_two_word() == '.':
                self.log('//调用其他函数')
                self.CompilersubroutineCall()
            elif True:
                # 说明是变量名，直接输出
                self.log('//变量名')
                self.xml_id(self.jacktoken.advance())#说明是变量名，直接输出
                #self.log('//变量名')
                #self.xml_id(self.jacktoken.advance())

        # 出现symbol有两种情况
        elif self.get_next_word_type() == SYMBOL:
            self.log('//term中出现symbol')
            # 用括号括起的表达式
            if self.get_next_word() == '(':
                # (
                self.xml_symbol(self.jacktoken.advance())

                self.CompilerExpression()

                # )
                self.xml_symbol(self.jacktoken.advance())
            # 无需前缀的term
            if self.get_next_word() in unaryop:
                self.log('无需前缀的term')
                self.xml_symbol(self.jacktoken.advance())
                self.CompilerTerm()

        elif True:
            raise('没有匹配的term')
        self.xml_end('term')

    def CompilerExpressionList(self):
        self.xml_begin('expressionList')
        if self.get_next_word() != ')' and self.get_next_word() != ']':
            self.CompilerExpression()
        while self.get_next_word() == ',':
            self.xml_symbol(self.jacktoken.advance())
            self.CompilerExpression()
        self.xml_end('expressionList')
        pass


    def CompilersubroutineCall(self):
        if self.get_next_two_word() == '(':
            # id
            self.xml_id(self.jacktoken.advance())
            # (
            self.xml_symbol(self.jacktoken.advance())

            self.CompilerExpressionList()

            # )
            self.xml_symbol(self.jacktoken.advance())
        if self.get_next_two_word() == '.':
            # classname/Varname
            self.xml_id(self.jacktoken.advance())
            # .
            self.xml_symbol(self.jacktoken.advance())

            self.xml_id(self.jacktoken.advance())

            # (
            self.xml_symbol(self.jacktoken.advance())

            self.CompilerExpressionList()

            # )
            self.xml_symbol(self.jacktoken.advance())

        pass

    def is_ClassVarDec(self):
        if self.get_now_required_type_word(KEYWORD, STATIC) or self.get_now_required_type_word(KEYWORD, FIELD):
            return True
        else:
            return False


    def is_subroutineDec(self):
        if self.get_now_required_type_word(KEYWORD, CONSTRUCTOR) or self.get_now_required_type_word(KEYWORD, METHOD) or self.get_now_required_type_word(KEYWORD, FUNCTION):
            return True
        else:
            return False

    def is_VarDec(self):
        if self.get_now_required_type_word(KEYWORD, VAR):
            return True
        else:
            return False

    def is_statement(self):
        if self.get_now_required_type_word(KEYWORD, LET):
            return LET
        if self.get_now_required_type_word(KEYWORD, IF):
            return IF
        if self.get_now_required_type_word(KEYWORD, DO):
            return DO
        if self.get_now_required_type_word(KEYWORD, WHILE):
            return WHILE
        if self.get_now_required_type_word(KEYWORD, RETURN):
            return RETURN

        return False



    def xml_end(self, str):
        self.outfile.write('</'+str+'>\n')
        self.log('</' + str + '>')


    def xml_begin(self, str):
        self.outfile.write('<'+str+'>\n')
        self.log('<'+str+'>')


    def xml_id(self, id):
        self.outfile.write('<identifier>'+id+'</identifier>\n')
        self.log('<identifier>'+id+'</identifier>')

    def xml_symbol(self, s):
        #print(s)
        if s in '<>&':
            if s == '<':
                s = '&lt;'
            if s == '>':
                s = '&gt;'
            if s == '&':
                s = '&amp;'

        self.outfile.write('<symbol>'+s+'</symbol>\n')
        self.log('<symbol>'+s+'</symbol>')


    def xml_int(self, integer_con):
        self.outfile.write('<integerConstant>'+integer_con+'</integerConstant>\n')
        self.log('<integerConstant>'+integer_con+'</integerConstant>')


    def xml_str(self, string):
        self.outfile.write('<stringConstant>'+string.split('"')+'</stringConstant>\n')
        self.log('<stringConstant>'+string+'</stringConstant>')

    def xml_keyword(self, key_word):
        self.outfile.write('<keyword>'+key_word+'</keyword>\n')
        self.log('<keyword>'+key_word+'</keyword>')

    def get_next_required_type_word(self, token_type, word_type=None):
        word = self.jacktoken._WordList[self.jacktoken._cur_word_num + 1]
        if self.jacktoken.TokenType(word) == token_type:
            if token_type != KEYWORD:
                return word
            elif self.jacktoken.keyword(word) == word_type:
                return word
            else:
                #print('关键字类型错误:期望的类型:')
                #print(word_type)
                #print('实际类型:')
                #print(self.jacktoken.keyword(word))
                #raise(TypeError)
                return False
        else:
            #print('字元类型错误:期望的类型:')
            #print(token_type)
            #print('实际类型:')
            #print(self.jacktoken.TokenType(word))
            #raise(TypeError)
            return False

    def get_now_required_type_word(self, token_type, word_type=None):
        word = self.jacktoken._WordList[self.jacktoken._cur_word_num]
        if self.jacktoken.TokenType(word) == token_type:
            if token_type != KEYWORD:
                return word
            elif self.jacktoken.keyword(word) == word_type:
                return word
            else:
                return False
        else:
            return False




    def get_required_symbol(self, symboltype):
        word = self.jacktoken.advance()
        if self.jacktoken.TokenType(word) == SYMBOL:
            if word == symboltype:
                #print(word)
                return word
            else:
                print('符号类型错误')
                #raise(TypeError)
        raise (TypeError)

    def get_next_word(self):
        return self.jacktoken._WordList[self.jacktoken._cur_word_num]


    def get_next_word_type(self):
        word = self.jacktoken._WordList[self.jacktoken._cur_word_num]
        return self.jacktoken.TokenType(word)


    def get_next_two_word(self):
        return self.jacktoken._WordList[self.jacktoken._cur_word_num + 1]

