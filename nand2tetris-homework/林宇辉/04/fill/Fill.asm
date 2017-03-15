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

    @8192
    D=A
    @screen_length
    M=D
    (INFINITE_LOOP)
    @KBD
    D=M
    @length
    M=-1
    @BLACKEN
    D; JNE
    @WHITEN
    D; JEQ
(BLACKEN)
    @length
    M=M+1
    D=M
    @SCREEN
    A=A+D
    M=-1
    @screen_length
    D=M-D
    D=D-1
    @BLACKEN
    D;JNE
    @INFINITE_LOOP
    D;JEQ
(WHITEN)
    @length
    M=M+1
    D=M
    @SCREEN
    A=A+D
    M=0
    @screen_length
    D=M-D
    D=D-1
    @WHITEN
    D;JNE
    @INFINITE_LOOP
    D;JEQ
