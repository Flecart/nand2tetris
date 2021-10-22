CC = gcc
# https://sqlite.org/forum/info/f79c49313a83f572 for -ldl -pthread
CFLAGS = -Wall -Werror -g
CPPFLAGS = -I$(HEADERS)

HEADERS = ./includes
SRC = ./src

ADIR = $(SRC)/a_instruction
CDIR = $(SRC)/c_instruction
GENDIR = $(SRC)/main_handlers

OBJS = assembler.o a_instruction.o AMap.o c_instruction.o CMap.o validators.o getters.o file_parser.o utils.o compiler.o

VPATH = $(SRC):$(ADIR):$(CDIR):$(GENDIR):$(HEADERS)

assembler: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(OBJS) -o $@
	make clean 

# If you wonder what is this weird sintax %.o : %.c 
# https://stackoverflow.com/questions/54854128/use-of-o-c-in-makefile/54892804
%.o : %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c 

assembler.o: 		assembler.c			utils.h		a_instruction.h 	c_instruction.h 	file_parser.h 	compiler.h
a_instruction.o: 	a_instruction.c  	utils.h  	a_instruction.h 	AMap.h
AMap.o: 			AMap.c  			utils.h 	AMap.h

c_instruction.o: 	c_instruction.c 	utils.h  	c_instruction.h  	validators.h
CMap.o: 			CMap.c 				utils.h 	CMap.h 
validators.o: 		validators.c 		utils.h 	validators.h
getters.o: 			getters.c 			

file_parser.o: 		file_parser.c 		utils.h
compiler.o: 		compiler.c 			utils.h
utils.o: 			utils.c 			utils.h

clean:
	rm $(OBJS)

