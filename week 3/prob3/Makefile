# Simple Makefile for sorting algorithms
CXX = g++
CXXFLAGS = -std=c++11

ALGO ?= merge
SIZE ?= 10000

all: sorting_test

sorting_test: sorting_test.cpp
	$(CXX) $(CXXFLAGS) -o sorting_test sorting_test.cpp

test: sorting_test
	./sorting_test $(ALGO) $(SIZE)

run: sorting_test
	./sorting_test $(ALGO) $(SIZE)

analyze: sorting_test
	chmod +x process.sh
	./process.sh
	gnuplot plot_time.gnu
	gnuplot plot_memory.gnu

clean:
	rm -f sorting_test *.png results/*.txt *.gnu

.PHONY: all test run analyze clean