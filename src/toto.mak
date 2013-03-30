CPP = g++ --std=c++0x
#Utilise pour avoir acces aux ajouts du c++11

#-Wall -std=c++0x

CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS = -O3
tarte = -O3

all : $(OBJ_FILES)
	$(CPP) -o $@ $^

%.o: %.cpp
	$(CPP) $(CC_FLAGS) $(tarte) -c -o $@ $<

clean :
	rm $(OBJ_FILES)
