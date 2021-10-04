(INPUT)
	// i = SCREEN MEMORY, PER IL LOOP
	@SCREEN
	D=A 
	@i
	M=D 

	// D=INPUT TASTIERA
	@KBD 
	D=M	

	// SE D=0 TORNA A PRENDERE INPUT
	@LOOPWHITE
	D;JEQ

	// ALTRIMENTI VADO A LOOP BLACK
	@LOOPBLACK
	D;JNE

(LOOPWHITE)
	// TRASFORMA IL BIT IN BIANCO
	@i
	A=M
	M=0
	
	// I = I + 1
	@i
	M=M+1

	// D = I - KBD UTILE PER COMPARARE
	// SE D=0 SIGNIFICA CHE I = KBD, QUINDI FINITO
	@i 
	D=M
	@KBD 
	D=D-A 

	// SE D!=0 NON HO FINITO QUINDI CONTINUA
	@LOOPWHITE
	D;JNE

	// ALTRIMENTI TORNA ALL'INIZIO
	@INPUT
	D;JEQ

(LOOPBLACK)
	// TRASFORMA IL BIT IN NERO
	@i
	A=M
	M=-1

	// I = I + 1
	@i
	M=M+1

	// D = I - KBD UTILE PER COMPARARE
	// SE D=0 SIGNIFICA CHE I = KBD, QUINDI FINITO
	@i 
	D=M
	@KBD 
	D=D-A 

	// SE D!=0 NON HO FINITO QUINDI CONTINUA
	@LOOPBLACK
	D;JNE

(END)
	@INPUT
	0;JMP


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