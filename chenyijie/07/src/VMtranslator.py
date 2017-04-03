import Parser
import codewriter
from constant import *
def main():
    filename = input('Enter filename:')
    #parse = Parser.Parser('in.vm')
    parser = Parser.Parser(filename)
    asmfile = filename.split('.',2)[0]+'.asm'
    Codewriter = codewriter.CodeWriter(asmfile)
    Codewriter.setfilename()
    while True:
        if parser.hasMorecommands():
            cur_command = parser.advance()
            if cur_command:
                print('----------------------------------------------')
                print(cur_command)
                #print(parser.CommandType(cur_command))
                if (parser.CommandType(cur_command) == C_PUSH)or(parser.CommandType(cur_command) == C_POP):
                    Codewriter.writePushPoP(parser.CommandType(cur_command),parser.arg1(), parser.arg2())
                if(parser.CommandType(cur_command) == C_ARITHMETIC):
                    Codewriter.writeArithmetic(cur_command)

        else:
            break

main()
print('compile succeed!')
enter = input('press Enter to continue.')
