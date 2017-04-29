#字元类型
KEYWORD      = 1
SYMBOL       = 2
IDENTIFIER   = 3
INT_CONST    = 4
STRING_CONST = 5

#字元关键字
CLASS        = 1
METHOD       = 2
INT          = 3
FUNCTION     = 4
BOOLEAN      = 5
CONSTRUCTOR  = 6
CHAR         = 7
VOID         = 8
VAR          = 9
STATIC       = 10
FIELD        = 11
LET          = 12
DO           = 13
IF           = 14
ELSE         = 15
WHILE        = 16
RETURN       = 17
TRUE         = 18
FALSE        = 19
NULL         = 20
THIS         = 21


# = ['class', 'constructor', 'method', 'int', 'function', 'boolean', 'char', 'void', 'var', 'static',
#            'field', 'let', 'do', 'if', 'else', 'while', 'return', 'true', 'false', 'null', 'this']
#tokentype = []


keywords = {'class': CLASS, 'constructor': CONSTRUCTOR, 'method': METHOD, 'int': INT, 'function': FUNCTION,
             'boolean': BOOLEAN, 'char': CHAR, 'void': VOID, 'var': VAR, 'static': STATIC, 'field': FIELD,
             'let': LET, 'do': DO, 'if': IF, 'else': ELSE, 'while': WHILE, 'return': RETURN, 'true': TRUE,
             'false': FALSE, 'null': NULL, 'this': THIS}


symbol = ['{', '}', '(', ')', '[', ']',
          '.', ',', ';', '+', '-', '*', '/',
          '&', '|', '<', '>', '=', '~']

keywordconstant = ['null','this', 'true', 'false']

op='+-*/|&<>='

unaryop = '~-'