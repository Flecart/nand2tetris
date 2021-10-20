(BEGIN)
	// if R0 < 0 then exit
	@R0
	D=M 
	@END
	D;JLT

	// if R1 < 0 then exit
	@R1
	D=M 
	@END
	D;JLT

(SETPARAMETERS)
	// for(int i = 0; i < R1; i++);
	D=0
	@i 
	M=D // I = 0

	@R2
	M=D // R2 = 0
	
(MULTIPLY)
	// if i == R1 exit
	@R1 
	D=M 
	@i 
	D=D-M 
	@END 
	D;JEQ


	// R2 = R0 + R2
	@R0
	D=M 
	@R2
	M=M+D 

	// I += 1
	@i 
	M=M+1 

	@MULTIPLY
	0;JMP 

(STORE)
	@R2
	D=M 
	@R2 
	M=D
	@END
	0;JMP

(END)
	@END
	0;JMP 

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768