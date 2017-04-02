#写入代码
from constant import *

class CodeWriter(object):
    """docstring fo CodeWriter."""
    def __init__(self, filename):

        self._filename = filename
        self._eq_label_num = 1
        self._ne_label_num = 1

    def setfilename(self):
        self._file = open(self._filename, 'w')

    def writeCommands(self,commands):
        for n in commands:
            self._file.write(n+'\n')
            print(n)

    def eq_label(self):
        return 'LABEL_SATISFY_'+str(self._eq_label_num)

    def ne_label(self):
        return 'LABEL_DISSATISIFY_'+str(self._ne_label_num)

    def writeArithmetic(self, command):
        if command == 'add':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=D+A','@SP','A=M','M=D','@SP','M=M+1'])
            #                   取出栈顶元素                      索引到第二个元素        相加        放回栈顶             索引归位
        if command == 'sub':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=A-D','@SP','A=M','M=D','@SP','M=M+1'])
            #                   取出栈顶元素                      索引到第二个元素        相减        放回栈顶             索引归位
        if command == 'eq':#x=y
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=A-D',
            '@'+self.eq_label(),'D;JEQ','@SP','A=M','M=0',#如果相等跳转，否则设置为0
            '@'+self.ne_label(),'0;JMP',#跳至不相等的情况
            '('+self.eq_label()+')','@SP','A=M','M=-1',#相等，置为-1
            '('+self.ne_label()+')','@SP','M=M+1'])
            #让标签数增加，防止重复出现
            self._eq_label_num = self._eq_label_num + 1
            self._ne_label_num = self._ne_label_num + 1

        if command == 'neg':#-y
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','D=-D','M=D','@SP','M=M+1'])
        if command == 'not':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','D=!D','M=D','@SP','M=M+1'])

        if command == 'gt':#x>y
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=A-D',
            '@'+self.eq_label(),'D;JGT','@SP','A=M','M=0',
            '@'+self.ne_label(),'0;JMP',
            '('+self.eq_label()+')','@SP','A=M','M=-1',
            '('+self.ne_label()+')','@SP','M=M+1'])
            self._eq_label_num = self._eq_label_num + 1
            self._ne_label_num = self._ne_label_num + 1
        if command == 'lt':#x<y
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=A-D',
            '@'+self.eq_label(),'D;JLT','@SP','A=M','M=0',
            '@'+self.ne_label(),'0;JMP',
            '('+self.eq_label()+')','@SP','A=M','M=-1',
            '('+self.ne_label()+')','@SP','M=M+1'])
            self._eq_label_num = self._eq_label_num + 1
            self._ne_label_num = self._ne_label_num + 1
        if command == 'and':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=A&D','@SP','A=M','M=D','@SP','M=M+1'])
        if command == 'or':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','D=A|D','@SP','A=M','M=D','@SP','M=M+1'])


    def writePushPoP(self, commandtype, arg1, arg2):
        number = arg2
        if commandtype == C_PUSH:
            if arg1 == 'constant':
                self.writeCommands(['@'+arg2, 'D=A','@SP','A=M','M=D','@SP','M=M+1'])
            if arg1 == 'local':
                self.writeCommands(['@'+arg2, 'D=A','@LCL','A=M','AD=D+A','D=M','@SP','A=M','M=D','@SP','M=M+1'])
            if arg1 == 'that':
                self.writeCommands(['@'+arg2, 'D=A','@THAT','A=M','AD=D+A','D=M','@SP','A=M','M=D','@SP','M=M+1'])
            if arg1 == 'this':
                self.writeCommands(['@'+arg2, 'D=A','@THIS','A=M','AD=D+A','D=M','@SP','A=M','M=D','@SP','M=M+1'])
            if arg1 == 'argument':
                self.writeCommands(['@'+arg2, 'D=A','@ARG','A=M','AD=D+A','D=M','@SP','A=M','M=D','@SP','M=M+1'])
            if arg1 == 'temp':
                self.writeCommands(['@'+arg2, 'D=A','@TEMP','A=M','AD=D+A','D=M','@SP','A=M','M=D','@SP','M=M+1'])
        if commandtype == C_POP:
            if arg1 == 'local':
                self.writeCommands(['@SP','M=M-1','@'+arg2, 'D=A','@LCL','A=M','AD=D+A','@R13','M=D','@SP','A=M','D=M','@R13','A=M','M=D'])
            if arg1 == 'argument':
                self.writeCommands(['@SP','M=M-1','@'+arg2, 'D=A','@ARG','A=M','AD=D+A','@R13','M=D','@SP','A=M','D=M','@R13','A=M','M=D'])
            if arg1 == 'this':
                self.writeCommands(['@SP','M=M-1','@'+arg2, 'D=A','@THIS','A=M','AD=D+A','@R13','M=D','@SP','A=M','D=M','@R13','A=M','M=D'])
            if arg1 == 'that':
                self.writeCommands(['@SP','M=M-1','@'+arg2, 'D=A','@THAT','A=M','AD=D+A','@R13','M=D','@SP','A=M','D=M','@R13','A=M','M=D'])
            if arg1 == 'temp':
                self.writeCommands(['@SP','M=M-1','@'+arg2, 'D=A','@TEMP','A=M','AD=D+A','@R13','M=D','@SP','A=M','D=M','@R13','A=M','M=D'])
        return
