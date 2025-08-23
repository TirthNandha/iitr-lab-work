SHELL = /bin/bash
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall
TARGETS = prob1 prob2 prob3
TIME_CMD = /usr/bin/time -f "%e,%M"

# Node sizes for VARN experiments (reduced for faster testing)
VARN_NODES = 50 75 100 125 150

# Edge sizes for VARM experiments (reduced for faster testing)
VARM_NODES = 50 75 100
# Will vary from 2n to n(n-1)/2

# Number of test runs per configuration (reduced for faster testing)
RUNS = 3

all: $(TARGETS)

prob1: prob1.cpp graph.h
	$(CXX) $(CXXFLAGS) -o prob1 prob1.cpp

prob2: prob2.cpp graph.h
	$(CXX) $(CXXFLAGS) -o prob2 prob2.cpp

prob3: prob3.cpp graph.h
	$(CXX) $(CXXFLAGS) -o prob3 prob3.cpp

clean:
	rm -f $(TARGETS) *.o
	rm -f results/*.txt
	rm -f plots/*.png

# Create directories for results and plots
dirs:
	mkdir -p results plots

# Run all experiments
experiments: all dirs run_prob1 run_prob2 run_prob3

# Problem 1 experiments
run_prob1:
	@echo "Running Problem 1 experiments..."
	@rm -f results/prob1_raw.txt
	@# VARM experiments
	@for n in $(VARM_NODES); do \
		m=$$((2*$$n)); \
		max_m=$$(($$n*($$n-1)/2)); \
		while [ $$m -le $$max_m ] && [ $$m -le $$((8*$$n)) ]; do \
			for run in `seq 1 $(RUNS)`; do \
				seed=$$(($$RANDOM)); \
				echo "VARM n=$$n m=$$m run=$$run"; \
				$(TIME_CMD) -o results/time_temp.txt ./prob1 VARM $$n $$m $$seed >> results/prob1_raw.txt 2>&1; \
			done; \
			m=$$(($$m*2)); \
		done; \
	done
	@# VARN experiments
	@for n in $(VARN_NODES); do \
		for sparsity in 1 2 4; do \
			for run in `seq 1 $(RUNS)`; do \
				seed=$$(($$RANDOM)); \
				echo "VARN n=$$n sparsity=$$sparsity run=$$run"; \
				$(TIME_CMD) -o results/time_temp.txt ./prob1 VARN $$n $$sparsity $$seed >> results/prob1_raw.txt 2>&1; \
			done; \
		done; \
	done

# Problem 2 experiments
run_prob2:
	@echo "Running Problem 2 experiments..."
	@rm -f results/prob2_raw.txt
	@# VARM experiments with different weight types
	@for n in $(VARM_NODES); do \
		m=$$((2*$$n)); \
		max_m=$$(($$n*($$n-1)/2)); \
		while [ $$m -le $$max_m ] && [ $$m -le $$((8*$$n)) ]; do \
			for weight_type in unweighted 01 wbfs_5; do \
				for run in `seq 1 $(RUNS)`; do \
					seed=$$(($$RANDOM)); \
					echo "VARM n=$$n m=$$m weight=$$weight_type run=$$run"; \
					$(TIME_CMD) -o results/time_temp.txt ./prob2 VARM $$n $$m $$weight_type $$seed >> results/prob2_raw.txt 2>&1; \
				done; \
			done; \
			m=$$(($$m*2)); \
		done; \
	done

# Problem 3 experiments
run_prob3:
	@echo "Running Problem 3 experiments..."
	@rm -f results/prob3_raw.txt
	@# VARM experiments
	@for n in $(VARM_NODES); do \
		m=$$((2*$$n)); \
		max_m=$$(($$n*($$n-1))); \
		while [ $$m -le $$max_m ] && [ $$m -le $$((8*$$n)) ]; do \
			for run in `seq 1 $(RUNS)`; do \
				seed=$$(($$RANDOM)); \
				echo "VARM n=$$n m=$$m run=$$run"; \
				$(TIME_CMD) -o results/time_temp.txt ./prob3 VARM $$n $$m $$seed >> results/prob3_raw.txt 2>&1; \
			done; \
			m=$$(($$m*2)); \
		done; \
	done
	@# VARN experiments
	@for n in $(VARN_NODES); do \
		for sparsity in 1 2 4; do \
			for run in `seq 1 $(RUNS)`; do \
				seed=$$(($$RANDOM)); \
				echo "VARN n=$$n sparsity=$$sparsity run=$$run"; \
				$(TIME_CMD) -o results/time_temp.txt ./prob3 VARN $$n $$sparsity $$seed >> results/prob3_raw.txt 2>&1; \
			done; \
		done; \
	done

# Process results and generate plots
process: 
	@echo "Processing results..."
	./process.sh
	@echo "Generating plots..."
	gnuplot plot.gnu

.PHONY: all clean dirs experiments run_prob1 run_prob2 run_prob3 process