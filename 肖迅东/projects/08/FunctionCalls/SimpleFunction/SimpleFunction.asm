// Input filename: SimpleFunction.vm
(SimpleFunction.test)
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M+D
@SP
M=M+1
@SP
AM=M-1
M=!M
@SP
M=M+1
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M+D
@SP
M=M+1
@1
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M-D
@SP
M=M+1
@LCL
D=M
@frame
M=D
@5
A=D-A
D=M
@ret
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D+1
@frame
D=M
D=D-1
@frame
M=D
A=D
D=M
@THAT
M=D
@frame
D=M
D=D-1
@frame
M=D
A=D
D=M
@THIS
M=D
@frame
D=M
D=D-1
@frame
M=D
A=D
D=M
@ARG
M=D
@frame
D=M
D=D-1
@frame
M=D
A=D
D=M
@LCL
M=D
@ret
A=M
0;JMP
(END)
@END
0;JMP