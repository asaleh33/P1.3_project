CXX=g++

CXXFLAGS=-Wall	-Wextra	-g	-ggdb

CPPFLAGS=-std=c++14

SRC=main.cpp

EXE=$(SRC:.cpp=.x)

all:$(EXE)

TREESIZE=5000

run:clean all
	./$(EXE)	$(TREESIZE)

%.x:%.cpp
	$(CXX)	$<	$(CXXFLAGS)	-o	$@	$(CPPFLAGS)


plot1:
	./plot_perf.py	benchmarking_data_unbalanced_avg.dat	benchmarking_data_balanced_avg.dat	benchmarking_data_map_avg.dat


plot2:
	./plot_balance_finditer.py	balance_time.dat	benchmarking_data_iter_avg.dat

clean:
	@rm	-f	*~	*.dat	*.txt	$(EXE)

.PHONY:clean
