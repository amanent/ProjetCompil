# Makefile pour le projet Compilation

OBJ = proj.o proj_l.o proj_y.o
CC = gcc
CFLAGS = -Wall -ansi -I./ -g 
LDFLAGS = -g -lfl

proj : $(OBJ)
	$(CC) -o proj $(OBJ) $(LDFLAGS)

proj.o : proj.c proj_y.h proj.h
	$(CC) $(CFLAGS) -c proj.c

proj_l.o: proj_l.c proj_y.h
	$(CC) $(CFLAGS) -c proj_l.c

proj_y.o : proj_y.c
	$(CC) $(CFLAGS) -c proj_y.c

proj.c :
	touch proj.c

proj_l.c : proj.l proj_y.h
	flex --yylineno --nounput -o proj_l.c proj.l

proj_y.h proj_y.c : proj.y proj.h
	bison -v -b proj_y -o proj_y.c -d proj.y

.Phony: clean tests
# feature interessante : indique que clean et tests ne sont pas des fichiers, mais bien des commander a executer, que les fichiers existent ou non.

clean:
	rm -f *~ proj *.o proj_l.* proj_y.*

tests:
	@make proj
	@./test.sh -r -v -a test
