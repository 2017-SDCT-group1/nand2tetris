// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

//JGT >0 to end
//JNG <0 to endWhile
//JMP goto loop
//x;xxx if x = 0 ; xxx
//j1      j2          j3
//(out < 0)(out = 0)(out > 0) Mnemonic     Effect
//   0         0        0       null      No jump
//   0         0        1       JGT    If out > 0 jump
//   0         1        0       JEQ    If out = 0 jump
//   0         1        1       JGE    If out b 0 jump
//   1         0        0       JLT    If out < 0 jump
//   1         0        1       JNE    If out !=0 jump
//   1         1        0       JLE    If out a 0 jump
//   1         1        1       JMP        Jump

@R0
D=M
@a
M=D
@R1
D=M
@b
M=D
@sum
M=0
(LOOP)
@a
D=M
@END
D;JEQ
@b
D=M
@sum
M=D+M
@a
M=M-1
@LOOP
0;JMP
(END)
@sum
D=M
@R2
M=D
(WHILE)
@WHILE
0;JMP