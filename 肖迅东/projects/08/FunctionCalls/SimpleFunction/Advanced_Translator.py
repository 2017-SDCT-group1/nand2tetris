operate_command = {"add": "+", "sub": "-",
                   "and": "&", "or": "|",
                   "not": "!", "neg": "-",
                   "lt": "JLT", "gt": "JGT",
                   "eq": "JEQ", "leq": "JLE",
                   "geq": "JGE"}

memory_operator = {"push", "pop"}

symbol_dict = {"this": ("THIS", "M"), "that": ("THAT", "M"), "argument": ("ARG", "M",), "local": ("LCL", "M",),
               "static": ("f.%d", "M",), "temp": ("5", "A",)}


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

call = "D=0\n" \
       + push_tail + "@LCL\nD=M\n"\
       + push_tail + "@ARG\nD=M\n"\
       + push_tail + "@THIS\nD=M\n"\
       + push_tail + "@THAT\nD=M\n" \
       + push_tail + "@SP\nD=M\nD=D-1\nD=D-1\nD=D-1\nD=D-1\nD=D-1\n"\
       + "%s"\
       + "@SP\nD=M\n@LCL\nM=D\n"
# cope with call

binary_operator = ["add","sub","and","or"]
unary_operator = ["not","neg"]
comp_operator = ["lt","gt","eq","leq","geq"]

output = ""
line_counter = 0
operator_counter = 0


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
        variables_num = operated_line.split()[2]
        return ""
    elif operator == "return":
        return return_function(operated_line)
    elif operator == "call":
        call_temp = ""
        i = 0
        while 1:
            if i == operated_line.split()[2]:
                break;
            call_temp += "D=D-1\n"
            i += 1
        return call % (call_temp)


def binary_function(operated_line):
    global operator_counter
    out = ""
    if operated_line in comp_operator:
        out += comp % (operator_counter, operate_command[operated_line], operator_counter, operator_counter, operator_counter, operator_counter, operator_counter)
        operator_counter += 1
    elif operated_line in unary_operator:
        out += unary % operate_command[operated_line]
    else:
        out += binary % operate_command[operated_line]
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


def call_function(operated_line):
    temp_output = ""
    open_file = operated_line.split()[1].split('.')[0] + '.vm'
    file = open(open_file,"r")
    status = 0
    while 1:
        for line in file:
            if(line.strip().split()[1] == operated_line.split()[1]):
                status = 1
            if (line.strip() == "return"):
                status = 0
            if (status == 1):
                temp_output += choose_function(line.strip())
            file.close()
            break
    return temp_output

def main():
    global output
    inputfname = input("input the file name:")
    outputfname = inputfname.split('.')[0] + ".asm"

    inputf = open(inputfname,"r")
    output += "// Input filename: %s\n" % inputfname
    while 1:
        for line in inputf:
            output += choose_function(line.strip())
        inputf.close()
        break

    outputf = open(outputfname, 'w')
    for outl in output:
        outputf.write(outl)
    outputf.write("(END)\n@END\n0;JMP")

    outputf.close()
    print("Output written to " + outputfname)

if __name__ == "__main__":
    main()