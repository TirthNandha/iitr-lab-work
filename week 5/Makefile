CXX = g++
CXXFLAGS = -pthread

all: part1 part2

part1: part1.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

part2: part2.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: part2
	./part2

plots:
	./generate_plots.sh

clean:
	rm -f part1 part2 *.png
	rm -rf results/
	rm -f input_*.txt

.PHONY: all run plots clean