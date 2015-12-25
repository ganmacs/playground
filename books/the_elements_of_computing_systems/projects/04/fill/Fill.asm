// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

(TOP)
  @KBD
  D=M
  @A
  D; JNE
  @B
  0; JMP

(A)
  @32767
  D=A
  @R4
  M=D
  @BS
  D; JNE

(B)
  @R4
  M=0
  @BS
  D; JNE

(BS)
  @SCREEN
  D=A
  @R0
  M=D

  @512
  D=A
  @R2
  M=D

(OTOP)
  @R2
  D=M
  @OEND
  D ; JEQ
  @R2
  M=M-1

  @32
  D=A
  @R1
  M=D

(BTOP)
  @R1
  D=M
  @BEND
  D ; JEQ
  @R1
  M=M-1

  @R4
  D=M

  @R0
  A=M
  M=D
  A=A+1

  @R0
  M=M+1
  @BTOP
  0 ; JMP
(BEND)

  @OTOP
  0 ; JMP
(OEND)

  @TOP
  0;JMP

//(TOP)
//  @KBD
//  D=M
//  @BS
//  D; JNE
//
//  @END
//  0;JMP
//(BS)
//  // i = 0
//  @R0
//  M=0
//(BBS)
//  // M[i+base]=1
//  @SCREEN
//  D=A
//  @R0
//  A=M+D
//  D=M
//  @32767
//  D=A
//
//  @R0
//  M=M+1
//  @BBS
//  0;JMP
//
//
////  @R0
////  M=M-1
////  @TOP
////  0;JMP
////
////
////  @BS
//(OBS)
//  @TOP
//  0;JMP
//(END)
