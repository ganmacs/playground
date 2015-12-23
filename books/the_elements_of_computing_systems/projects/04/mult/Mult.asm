// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

  @R2
  M=0
(TOP)
  @R0
  D=M
  @END
  D; JEQ

  // R2=R2+R1
  @R2
  D=M
  @R1
  D=D+M
  @R2
  M=D

  //R1=R1-1
  @R0
  M=M-1
  @TOP
  0;JMP

(END)
