import Parser
import codewriter
from constant import *


def main():

    #asmfile = filename.split('.',2)[0]+'.asm'
    while True:
        if parser.hasMorecommands():
            cur_command = parser.advance()
            if cur_command:
                print('----------------------------------------------')
                print(cur_command)
                #print(parser.CommandType(cur_command))
                command_type = parser.CommandType(cur_command)#获取命令类型
                if (command_type == C_PUSH)or(command_type == C_POP):#Push和PoP
                    Codewriter.writePushPoP(command_type,parser.arg1(), parser.arg2())
                elif(command_type == C_ARITHMETIC):#运算
                    Codewriter.writeArithmetic(cur_command)
                elif(command_type == C_IF):
                    Codewriter.writeIf(parser.arg1())
                elif(command_type == C_GOTO):
                    Codewriter.writeGoto(parser.arg1())
                elif(command_type == C_LABEL):
                    Codewriter.writeLabel(parser.arg1())
                elif(command_type == C_FUNCTION):
                    Codewriter.witreFunction(parser.arg1(), parser.arg2())
                elif(command_type == C_RETURN):
                    Codewriter.writeReturn()
                elif(command_type == C_CALL):
                    Codewriter.writeCall(parser.arg1(), parser.arg2())
                elif True:
                    print('ERROR AT COMMAND:', cur_command)
                    break
        else:
            break



multfiles = False
filename = input('Enter filename:')
asmfile = input('Enter the ASM filename:')
Codewriter = codewriter.CodeWriter(asmfile)
Codewriter.setfilename()
filelist=filename.split()
Codewriter.writeInit()#输出初始化函数
for vmfile in filelist:
    parser = Parser.Parser(vmfile)
    main()


print('compile succeed!')
enter = input('press Enter to continue.')
