# Makefile pour le projet Compilation

OBJ = proj.o proj_l.o proj_y.o class.o function.o tree.o print.o  verifContext.o symboles.o variable.o gencode.o
CC = gcc
CFLAGS = -Wall -ansi -I./ -g -std=c99 #-Werror
LDFLAGS = -g -lfl
PROG = gaouc
PATH = ../bin/

all: $(OBJ)
	$(CC) -o $(PATH)$(PROG) $(OBJ) $(LDFLAGS)

proj.o: proj.c proj_y.h proj.h
	$(CC) $(CFLAGS) -c proj.c

proj_l.o: proj_l.c proj_y.h
	$(CC) $(CFLAGS) -c proj_l.c

proj_y.o: proj_y.c
	$(CC) $(CFLAGS) -c proj_y.c

proj.c:
	touch proj.c

proj_l.c: proj.l proj_y.h
	flex --yylineno --nounput -o proj_l.c proj.l

proj_y.h proj_y.c: proj.y proj.h
	bison -v -b proj_y -o proj_y.c -d proj.y

.Phony: clean mrproper tes1t test2 test3 test4 test5
# feature interessante : indique que clean et tests ne sont pas des fichiers, mais bien des commander a executer, que les fichiers existent ou non.

clean:
	rm -f *~ *.o proj_l.* proj_y.*

mrproper: clean
	rm -f $(PATH)$(PROG)

redo: mrproper all

test1:
	@make
	@$(PATH)$(PROG) -o $(PATH)test1.simple $(PATH)test1.mls 
	@../utils/Interprete/interp $(PATH)test1.simple

test2:
	@make
	@$(PATH)$(PROG) -o $(PATH)test2.simple $(PATH)test2.mls 
	@../utils/Interprete/interp $(PATH)test2.simple

test3:
	@make
	@$(PATH)$(PROG) -o $(PATH)test3.simple $(PATH)test3.mls 
	@../utils/Interprete/interp $(PATH)test3.simple

test4:
	@make
	@$(PATH)$(PROG) -o $(PATH)test4.simple $(PATH)test4.mls 
	@../utils/Interprete/interp $(PATH)test4.simple

test5:
	@make
	@$(PATH)$(PROG) -o $(PATH)test5.simple $(PATH)test5.mls 
	@../utils/Interprete/interp $(PATH)test5.simple