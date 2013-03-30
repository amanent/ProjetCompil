
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

CPP = g++

CFLAGS = -Wall --std=c++11
LDFLAGS = -g -lfl

PROG = proj

all : $(OBJ_FILES)
	$(CPP) -o $(PROG) $(OBJ_FILES) $(CFLAGS) $(LDFLAGS)


proj.o : proj.c proj_y.h proj.h
	$(CC) $(CFLAGS) -c proj.cpp

proj_l.o: proj_l.cpp proj_y.h
	$(CC) $(CFLAGS) -c proj_l.cpp

proj_y.o : proj_y.cpp
	$(CC) $(CFLAGS) -c proj_y.cpp

proj_l.cpp : proj.l proj_y.h
	flex --yylineno --nounput -o proj_l.cpp proj.l

proj_y.h proj_y.cpp : proj.y proj.h
	bison -v -b proj_y -o proj_y.cpp -d proj.y

%.o: %.cpp proj.o proj_y.o proj_l.o
	$(CPP) $(CC_FLAGS) --std=c++11 -c -o $@ $<


clean:
	rm -f *~ *.o proj_l.* proj_y.*

mrproper: clean
	rm -f $(PROG)
	
test:
	@make
	@./$(PROG) ../test/cast1.mls
