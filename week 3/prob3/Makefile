CXX = g++
CXXFLAGS = -std=c++17 -O2
ALGORITHMS = bubble selection merge quick rquick heap
INPUT_SIZE = 10000
RUNS = 100

all: $(ALGORITHMS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(ALGORITHMS)
	@for algo in $(ALGORITHMS); do \
		echo "Running $$algo..."; \
		rm -f summary.txt; \
		for i in $$(seq 1 $(RUNS)); do \
			/usr/bin/time -f "TOTAL %U %M" -o tmp_summary.txt --append ./$$algo $(INPUT_SIZE); \
		done; \
		mv tmp_summary.txt $$algo_summary.txt; \
	done

summarize:
	@bash process.sh

plot:
	gnuplot -p plot.gnuplot

clean:
	rm -f $(ALGORITHMS) *_summary.txt data.txt plot.png
