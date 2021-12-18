CC = gcc
CFLAGS = -Wall -g
CPPFLAGS = -I$(HEADERS)

HEADERS = ./includes
SRC = ./src
GENDIR = $(SRC)/main_handlers
TRANSLATE = $(SRC)/translate

OBJS = VMTranslator.o file_parser.o utils.o stackAritmetic.o aritTrans.o compiler.o programFlow.o functions.o walk_dir.o globals.o cacheFunc.o

VPATH = $(SRC):$(GENDIR):$(HEADERS):$(TEST):$(TRANSLATE)

VMTranslator: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(OBJS) -o $@
	make clean 

%.o : %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c 

VMTranslator.o: 	VMTranslator.c      

# compiler zone
compiler.o: 		compiler.c 			compiler.h 	stackAritmetic.o utils.o programFlow.o

programFlow.o: 		programFlow.c 		utils.h 	programFlow.h 

functions.o: 		functions.c  		functions.h utils.h aritTrans.h programFlow.h globals.h cacheFunc.h

stackAritmetic.o: 	stackAritmetic.c	utils.h		aritTrans.o
aritTrans.o: 		aritTrans.c			aritTrans.h globals.h
globals.o: 			globals.c 			globals.h
cacheFunc.o: 		cacheFunc.c			cacheFunc.h
# end zone

# file input management and general utilities
file_parser.o: 		file_parser.c 		utils.h
utils.o: 			utils.c 			utils.h
walk_dir.o:			walk_dir.c  		walk_dir.h
clean:
	rm $(OBJS)
