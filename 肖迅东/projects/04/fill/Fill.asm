// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
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

(WHILE)
@KBD
D=M
@i
M=0
@ELSE
D;JEQ
(IF)
@i
D=M
@SCREEN
A=A+D
M=-1
@i
M=M+1
D=M
D=M+D
@SCREEN
D=A-D
@IF
D;JGT
@WHILE
D;JEQ
(ELSE)
@i
D=M
@SCREEN
A=A+D
M=0
@i
M=M+1
D=M
D=M+D
@SCREEN
D=A-D
@ELSE
D;JGT
@WHILE
D;JEQ