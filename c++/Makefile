CXX=g++

CXXFLAGS=-Wall	-Wextra	-g	-ggdb

#CXXFLAGS=-g	-ggdb

CPPFLAGS=-std=c++14

SRC=main.cpp

EXE=$(SRC:.cpp=.x)

all:$(EXE)

run:clean all
	./$(EXE)

%.x:%.cpp
	$(CXX)	$<	$(CXXFLAGS)	-o	$@	$(CPPFLAGS)


plot:
	@gnuplot	-p	*gnu


clean:
	@rm	-f	*~	*.dat	*.txt	$(EXE)

.PHONY:clean
