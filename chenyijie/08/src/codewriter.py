#写入代码
from constant import *

class CodeWriter(object):
    """docstring fo CodeWriter."""
    def __init__(self, filename):

        self._filename = filename
        self._eq_label_num = 1
        self._ne_label_num = 1
        self._label_num = 1


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


    def label(self):
        return 'LABEL_'+str(self._label_num)


    def writeArithmetic(self, command):
        if command == 'add':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=D+A','@SP','A=M','M=D','@SP','M=M+1'])
            #                   取出栈顶元素                      索引到第二个元素                相加              放回栈顶             索引归位
        if command == 'sub':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=A-D','@SP','A=M','M=D','@SP','M=M+1'])
            #                   取出栈顶元素                      索引到第二个元素                相减              放回栈顶             索引归位
        if command == 'eq':#x=y
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=A-D',
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
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=A-D',
            '@'+self.eq_label(),'D;JGT','@SP','A=M','M=0',
            '@'+self.ne_label(),'0;JMP',
            '('+self.eq_label()+')','@SP','A=M','M=-1',
            '('+self.ne_label()+')','@SP','M=M+1'])
            self._eq_label_num = self._eq_label_num + 1
            self._ne_label_num = self._ne_label_num + 1
        if command == 'lt':#x<y
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=A-D',
            '@'+self.eq_label(),'D;JLT','@SP','A=M','M=0',
            '@'+self.ne_label(),'0;JMP',
            '('+self.eq_label()+')','@SP','A=M','M=-1',
            '('+self.ne_label()+')','@SP','M=M+1'])
            self._eq_label_num = self._eq_label_num + 1
            self._ne_label_num = self._ne_label_num + 1
        if command == 'and':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=A&D','@SP','A=M','M=D','@SP','M=M+1'])
        if command == 'or':
            self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@SP','M=M-1','@SP','A=M','A=M','D=A|D','@SP','A=M','M=D','@SP','M=M+1'])


    def writePushPoP(self, commandtype, arg1, arg2):
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
            if arg1 == 'static':
                self.writeCommands(['@'+arg2, 'D=M','@SP','A=M','M=D','@SP','M=M+1'])
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
            if arg1 == 'pointer':#为什么会不一样？
                self.writeCommands(['@SP','M=M-1','@'+arg2, 'D=A','@3','AD=D+A','@R13','M=D','@SP','A=M','D=M','@R13','A=M','M=D'])
            if arg1 == 'static':#为什么会不一样？
                self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@'+arg2,'M=D'])
    def writeInit(self):
        #SP=256
        self.writeCommands(['@256','D=A','@SP','M=D'])
        #call Sys.init
        self.writeCall('Sys.init', '0')


    def writeLabel(self, label):
        self.writeCommands(['('+label+')'])


    def writeGoto(self, label):
        self.writeCommands(['@'+label,'0;JMP'])


    def writeIf(self, label):#将布尔表达式的值从栈顶弹出，如果非0则跳转
        self.writeCommands(['@SP','M=M-1','@SP','A=M','D=M','@'+label,'D;JNE'])


    def writeCall(self, FunctionName, NumArgs):
        NumArgs = int(NumArgs)
        #push return-adress
        self.writeCommands(['@'+self.label(),'D=A','@SP','A=M','M=D','@SP','M=M+1'])
        #push LCL
        self.writeCommands(['@LCL','D=M','@SP','A=M','M=D','@SP','M=M+1'])
        #push ARG
        self.writeCommands(['@ARG','D=M','@SP','A=M','M=D','@SP','M=M+1'])
        #push THIS
        self.writeCommands(['@THIS','D=M','@SP','A=M','M=D','@SP','M=M+1'])
        #push THAT
        self.writeCommands(['@THAT','D=M','@SP','A=M','M=D','@SP','M=M+1'])
        #ARG=SP-n-5
        self.writeCommands(['@'+str(5+NumArgs),'D=A','@SP','A=M','AD=A-D','@ARG','M=D'])
        #LCL=SP
        self.writeCommands(['@SP','D=M','@LCL','M=D'])
        #goto f
        self.writeCommands(['@'+FunctionName,'0;JMP'])
        #(return-address)
        self.writeCommands(['('+self.label()+')'])

        self._label_num = self._label_num+1


    def writeReturn(self):
        #FRAME=LCL
        self.writeCommands(['@LCL','D=M','@FRAME','M=D'])
        #RET=*(FRAME-5)
        self.writeCommands(['@5','A=D-A','D=M','@RET','M=D'])
        #*ARG=POP()
        self.writeCommands(['@SP','M=M-1','@ARG','AD=M','@R15','M=D','@SP','A=M','D=M','@R15','A=M','D=M'])
        #SP=ARG+1
        self.writeCommands(['@ARG','D=M','@SP','M=D+1'])
        #THAT=*(FRAME-1)
        self.writeCommands(['@FRAME','D=M','D=D-1','@FRAME','M=D','A=D','D=M','@THAT','M=D'])
        #THIS=*(FRAME-2)
        self.writeCommands(['@FRAME','D=M','D=D-1','@FRAME','M=D','A=D','D=M','@THIS','M=D'])
        #ARG=*(FRAME-3)
        self.writeCommands(['@FRAME','D=M','D=D-1','@FRAME','M=D','A=D','D=M','@ARG','M=D'])
        #LCL=*(FRAME-4)
        self.writeCommands(['@FRAME','D=M','D=D-1','@FRAME','M=D','A=D','D=M','@LCL','M=D'])
        #goto RET
        self.writeCommands(['@RET','A=M','0;JMP'])


    def witreFunction(self, FunctionName, NumLocals):
        self.writeLabel(FunctionName)#为函数入口声明一个标签
        NumLocals = int(NumLocals)
        i = 0
        while i<NumLocals:#重复k次，初始化k个局部变量为0
            i=i+1
            self.writeCommands(['@0','D=A','@SP','A=M','M=D','@SP','M=M+1'])
