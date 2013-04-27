# Makefile pour le projet Compilation

OBJ = proj.o proj_l.o proj_y.o class.o function.o tree.o print.o  verifContext.o symboles.o variable.o gencode.o
CC = gcc
CFLAGS = -Wall -ansi -I./ -g -std=c99 #-Werror
LDFLAGS = -g -lfl
PROG = gaouc 

all: $(OBJ)
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS)

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

.Phony: clean mrproper tests
# feature interessante : indique que clean et tests ne sont pas des fichiers, mais bien des commander a executer, que les fichiers existent ou non.

clean:
	rm -f *~ *.o proj_l.* proj_y.*

mrproper: clean
	rm -f $(PROG)

redo: mrproper all

test:
	@make
	@./$(PROG) test4.mls 1> test4.simple
	#@../utils/Interprete/interp test4.simple

