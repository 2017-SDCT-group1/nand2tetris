import re


class Parser(object):
    """docstring for Parser."""

    def __init__(self, filename):
        try:
            f = open(filename, 'r')
            self.jack = f.read()
        except BaseException:
            print('打开文件错误')

    def remove_comments(self):#remove comments
        re_comment = re.compile(r'//[^\n]*\n|/\*(.*)?\*/', re.MULTILINE|re.DOTALL)
        return re_comment.sub(' ', self.jack)
