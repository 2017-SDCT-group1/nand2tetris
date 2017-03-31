#写入代码
import parser

def main():
    filename = input('Enter filename:\n')
    parse = parser.Parser(filename)
    while True:
        if parse.hasMorecommands():
            parse.advance()
        else:
            break

main()
