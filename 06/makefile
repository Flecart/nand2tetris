CC = gcc
CFLAGS = -Wall -Werror -g
CPPFLAGS = -I$(HEADERS)

HEADERS = ./includes
SRC = ./
GENDIR = $(SRC)/main_handlers
TEST = $(SRC)/test

OBJS = VMTranslator.o file_parser.o utils.o 

VPATH = $(SRC):$(GENDIR):$(HEADERS):$(TEST)

VMTranslator: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(OBJS) -o $@
	make clean 

TMP = stackAritmetic.o utils.o aritTrans.o
stackAritmetic: $(TMP)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(TMP) -o $@
	make clean2

stack_test: aritTrans.o stack_test.o utils.o
	$(CC) $(CFLAGS) $(CPPFLAGS) aritTrans.o stack_test.o utils.o -o $@
	rm *.o

%.o : %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c 

VMTranslator.o: 	VMTranslator.c      

stackAritmetic.o: 	stackAritmetic.c	utils.h
aritTrans.o: 		aritTrans.c			aritTrans.h

file_parser.o: 		file_parser.c 		utils.h
compiler.o: 		compiler.c 			utils.h
utils.o: 			utils.c 			utils.h

stack_test.o: 		stack_test.c

clean:
	rm $(OBJS)

clean2: 
	rm $(TMP)