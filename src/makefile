# Makefile pour le projet Compilation

OBJ = proj.o proj_l.o proj_y.o class.o function.o tree.o print.o  verifContext.o symboles.o variable.o gencode.o
CC = gcc
CFLAGS = -Wall -ansi -I./ -g -std=c99 #-Werror
LDFLAGS = -g -lfl
PROG = gaouc
PROGPATH = ../bin/

all: $(OBJ)
	$(CC) -o $(PROGPATH)$(PROG) $(OBJ) $(LDFLAGS)

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

.Phony: clean cleanTest redo mrproper tes1t test2 test3 test4 test5
# feature interessante : indique que clean et tests ne sont pas des fichiers, mais bien des commander a executer, que les fichiers existent ou non.

clean:
	rm -f *~ *.o proj_l.* proj_y.*

cleanTest:
	rm -f $(PROGPATH)*.simple

mrproper: clean
	rm -f $(PROGPATH)$(PROG)

redo: mrproper all

test1:
	@make
	@$(PROGPATH)$(PROG) -o $(PROGPATH)test1.simple $(PROGPATH)test1.mls 
	@../utils/Interprete/interp $(PROGPATH)test1.simple

test2:
	@make
	@$(PROGPATH)$(PROG) -o $(PROGPATH)test2.simple $(PROGPATH)test2.mls 
	@../utils/Interprete/interp $(PROGPATH)test2.simple

test3:
	@make
	@$(PROGPATH)$(PROG) -o $(PROGPATH)test3.simple $(PROGPATH)test3.mls 
	@../utils/Interprete/interp $(PROGPATH)test3.simple

test4:
	@make
	@$(PROGPATH)$(PROG) -o $(PROGPATH)test4.simple $(PROGPATH)test4.mls 
	@../utils/Interprete/interp $(PROGPATH)test4.simple

test5:
	@make
	@$(PROGPATH)$(PROG) -o $(PROGPATH)test5.simple $(PROGPATH)test5.mls 
	@../utils/Interprete/interp $(PROGPATH)test5.simple