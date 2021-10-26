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

%.o : %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c 

VMTranslator.o: 	VMTranslator.c      

file_parser.o: 		file_parser.c 		utils.h
compiler.o: 		compiler.c 			utils.h
utils.o: 			utils.c 			utils.h

clean:
	rm $(OBJS)

