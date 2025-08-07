CXX = g++
CXXFLAGS = -O2
INPUT_SIZE = 10000
TEST_CASES = 100
ALGORITHMS = bubble selection merge heap quick rquick

all: $(ALGORITHMS)

bubble: bubble.cpp
	$(CXX) $(CXXFLAGS) -o bubble bubble.cpp

selection: selection.cpp
	$(CXX) $(CXXFLAGS) -o selection selection.cpp

merge: merge.cpp
	$(CXX) $(CXXFLAGS) -o merge merge.cpp

heap: heap.cpp
	$(CXX) $(CXXFLAGS) -o heap heap.cpp

quick: quick.cpp
	$(CXX) $(CXXFLAGS) -o quick quick.cpp

rquick: rquick.cpp
	$(CXX) $(CXXFLAGS) -o rquick rquick.cpp

run:
	@echo "Running all algorithms..."
	@start=$$(date +%s.%N); \
	/usr/bin/time -f "%M" -o mem_all.txt bash -c '\
		for algo in $(ALGORITHMS); do \
			for i in `seq 1 $(TEST_CASES)`; do \
				./$$algo $(INPUT_SIZE); \
			done; \
		done'; \
	end=$$(date +%s.%N); \
	total_time=$$(echo "$$end - $$start" | bc); \
	mem=$$(cat mem_all.txt); \
	echo "Total_Time(ms) Max_Memory(KB)" > summary.txt; \
	echo "$$(echo "$$total_time * 1000" | bc) $$mem" >> summary.txt

clean:
	rm -f $(ALGORITHMS) *.txt
