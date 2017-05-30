operate_command = {"add": "+", "sub": "-",
                   "and": "&", "or": "|",
                   "not": "!", "neg": "-",
                   "lt": "JLT", "gt": "JGT",
                   "eq": "JEQ", "leq": "JLE",
                   "geq": "JGE"}

memory_operator = {"push", "pop"}

symbol_dict = {"this": ("THIS", "M"), "that": ("THAT", "M"), "argument": ("ARG", "M",), "local": ("LCL", "M",),
               "static": ("f.%d", "M",), "temp": ("5", "A",)}

function_dict = set()

start = "@SP\nAM=M-1\n"
end = "@SP\nM=M+1\n"

if_goto = start + "D=M\n@%s\nD;JNE\n"

goto = "@%s\n0;JMP\n"

binary = start + "D=M\n@SP\nAM=M-1\nM=M%sD\n" + end
# cope with + -,firstly find the operated num

unary = start + "M=%sM\n" + end
# cope with ! -

comp = start + "D=M\n@SP\nAM=M-1\nD=M-D\n\
@COMP.%d.TRUE\nD;%s\n\
@COMP.%d.FALSE\n0;JMP\n\
(COMP.%d.TRUE)\n\
@SP\nA=M\nM=-1\n@SP\nM=M+1\n\
@COMP.%d.END\n0;JMP\n\
(COMP.%d.FALSE)\n\
@SP\nA=M\nM=0\n" + end + "(COMP.%d.END)\n"
# cope with compare; if TRUE M=-1 else M=0

push_tail = "@SP\nA=M\nM=D\n@SP\nM=M+1\n"
# general used tail

push_const = "@%d\nD=A\n" + push_tail
# cope with constant

push_symbol = "@%d\nD=A\n@%s\nA=%s+D\nD=M\n" + push_tail
# cope with symbol

push_pointer = "@%s\nD=M\n" + push_tail
# cope with pointer

pop = "@%d\nD=A\n@%s\nD=%s+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"
#cope with pop

pop_pointer = "@SP\nAM=M-1\nD=M\n@%s\nM=D\n"
# cope with pop pointer

call = "@return%d\nD=A\n" + push_tail \
       + "@LCL\nD=M\n" + push_tail \
       + "@ARG\nD=M\n" + push_tail \
       + "@THIS\nD=M\n" + push_tail \
       + "@THAT\nD=M\n" + push_tail \
       + "@5\nD=A\n@%d\nD=A+D\n@SP\nD=M-D\n" \
       + "@ARG\nM=D\n" \
       + "@SP\nD=M\n@LCL\nM=D\n" \
       + "@%s\n0;JMP\n"\
       + "(return%d)\n"
# cope with call

return_tail = "@LCL\nD=M\n@frame\nM=D\n"\
              + "@5\nA=D-A\nD=M\n@ret\nM=D\n"\
              + "@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D\n"\
              + "@ARG\nD=M\n@SP\nM=D+1\n"\
              + "@frame\nD=M\nD=D-1\n@frame\nM=D\nA=D\nD=M\n@THAT\nM=D\n"\
              + "@frame\nD=M\nD=D-1\n@frame\nM=D\nA=D\nD=M\n@THIS\nM=D\n" \
              + "@frame\nD=M\nD=D-1\n@frame\nM=D\nA=D\nD=M\n@ARG\nM=D\n" \
              + "@frame\nD=M\nD=D-1\n@frame\nM=D\nA=D\nD=M\n@LCL\nM=D\n" \
              + "@ret\nA=M\n0;JMP\n"

binary_operator = ["add","sub","and","or"]
unary_operator = ["not","neg"]
comp_operator = ["lt","gt","eq","leq","geq"]

output = ""
line_counter = 0
operator_counter = 0
inputfname = ""
return_address = 0


def choose_function (operated_line):
    global line_counter
    global variables_num
    global return_address

    if (operated_line[0: 2] == "//") or (len(operated_line.split()) == 0):
        return ""
    # cope with // and space and \n
    operator = operated_line.split()[0]
    line_counter += 1
    if operator in operate_command:
        return binary_function(operated_line)
    elif operator in memory_operator:
        return unary_function(operated_line)
    elif operator == "label":
        return label_function(operated_line)
    elif operator == "if-goto":
        return if_goto_function(operated_line)
    elif operator == "goto":
        return goto_function(operated_line)
    elif operator == "function":
        return function(operated_line,)
    elif operator == "return":
        return return_tail
    elif operator == "call":
        return_address += 1
        function_dict.add(operated_line.split()[0] + " " + operated_line.split()[1] + " " + operated_line.split()[2])
        return call % (return_address - 1, int(operated_line.split()[2]),
                       operated_line.split()[1], return_address - 1)


def binary_function(operated_line):
    global operator_counter
    ope = operated_line.split()[0]
    out = ""
    if ope in comp_operator:
        out += comp % (operator_counter, operate_command[ope], operator_counter, operator_counter, operator_counter, operator_counter, operator_counter)
        operator_counter += 1
    elif ope in unary_operator:
        out += unary % operate_command[ope]
    else:
        out += binary % operate_command[ope]
    return out


def unary_function(operated_line):
    global output
    instructions = operated_line.split()
    inst = instructions[0]
    argtype = instructions[1]
    val = int(instructions[2])
    if inst == "push":
        if argtype == "constant":
            return push_const % val
        elif argtype == "static":
            return push_pointer % ("f." + str(val))
        elif argtype == "pointer":
            if val == 0:
                return push_pointer % ("THIS")
            else:
                return push_pointer % ("THAT")
        else:
            return push_symbol % (val, symbol_dict[argtype][0], symbol_dict[argtype][1])
    elif inst == "pop":
        if argtype != "constant":
            if argtype == "static":
                return pop_pointer % ("f." + str(val))
            elif argtype == "pointer":
                if val == 0:
                    return pop_pointer % "THIS"
                else:
                    return pop_pointer % "THAT"
            else:
                return pop % (val, symbol_dict[argtype][0], symbol_dict[argtype][1])


def label_function(operated_line):
    return "(" + operated_line.split()[1] + ")\n"


def if_goto_function(operated_line):
    return if_goto % (operated_line.split()[1])


def goto_function(operated_line):
    return goto % (operated_line.split()[1])


def function(operated_line):
    temp = "(" + operated_line.split()[1] + ")\n"
    i = 0
    while True:
        i += 1
        t = operated_line.split()[2]
        if int(i) <= int(operated_line.split()[2]):
            temp += push_const % (0)
            continue
        else:
            break
    return temp


def call_function(operated_line,n):
    global function_num
    temp_output = ""
    open_file = operated_line.split()[1].split('.')[0] + '.vm'
    file = open(open_file,"r")
    status = 0
    while 1:
        for line in file:
            if(line.strip().split()[1] == operated_line.split()[1]):
                temp_output += call % (function_num, line.strip().split()[1], return_address)
                status = 1
                temp_output +=  function(line.split())
            if status == 1:
                if line.strip() != "return":
                    temp_output += choose_function(line.strip())
                else:
                    temp_output += return_tail % (n)
                    break
            file.close()
            break
    return temp_output


def main():
    global output
    global inputfname
    inputfname = input("input-file's name:")
    outputfname = input("output-file's name:")


    inputf = open(inputfname,"r")
    output += "// Input filename: %s\n" % inputfname
    while 1:
        for line in inputf:
            output += choose_function(line.strip())
        inputf.close()
        break

    for operated_line in function_dict:
        if operated_line.split()[1].split('.')[0] == inputfname.split('.')[0]:
            break;
        file_temp = open(operated_line.split()[1].split('.')[0] + ".vm")
        while 1:
            for line in file_temp:
                output += choose_function(line)
            file_temp.close()
            break;

    outputf = open(outputfname, 'w')
    for outl in output:
        outputf.write(outl)
    outputf.write("(END)\n@END\n0;JMP")

    outputf.close()
    print("Output written to " + outputfname)

if __name__ == "__main__":
    main()