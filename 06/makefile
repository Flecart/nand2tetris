CC = gcc
CFLAGS = -Wall -Werror -g
CPPFLAGS = -I$(HEADERS)

HEADERS = ./includes
SRC = ./
GENDIR = $(SRC)/main_handlers

OBJS = VMTranslator.o file_parser.o utils.o 

VPATH = $(SRC):$(GENDIR):$(HEADERS)

VMTranslator: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(OBJS) -o $@
	make clean 

TMP = stackAritmetic.o utils.o aritTrans.o
stackAritmetic: $(TMP)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(TMP) -o $@
%.o : %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c 

VMTranslator.o: 	VMTranslator.c      

stackAritmetic.o: 	stackAritmetic.c	utils.h
aritTrans.o: 		aritTrans.c			aritTrans.h 

file_parser.o: 		file_parser.c 		utils.h
compiler.o: 		compiler.c 			utils.h
utils.o: 			utils.c 			utils.h

clean:
	rm $(OBJS)

clean2: 
	rm $(TMP)