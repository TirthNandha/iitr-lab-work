# Enhanced Makefile for Sorting Algorithm Analysis
# Usage: 
#   make all          - Compile all algorithms
#   make test         - Run single test
#   make analyze      - Run complete analysis and generate plots
#   make clean        - Clean generated files

CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

# Source file (assuming your main C++ file is sorting_test.cpp)
MAIN_SOURCE = sorting_test.cpp
EXECUTABLE = sorting_test

# Algorithm types (used as compile-time arguments)
ALGORITHMS = MERGE QUICK RANDOMIZED_QUICK HEAP BUBBLE SELECTION

# Default values
ALGO ?= MERGE
SIZE ?= 10000

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

.PHONY: all clean test analyze plots help

# Default target
all: $(EXECUTABLE)
	@echo "$(GREEN)All algorithms compiled successfully!$(NC)"

# Compile the main executable
$(EXECUTABLE): $(MAIN_SOURCE)
	@echo "$(YELLOW)Compiling sorting algorithms...$(NC)"
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run a single test case
test: $(EXECUTABLE)
	@echo "$(YELLOW)Running $(ALGO) with $(SIZE) elements...$(NC)"
	@/usr/bin/time -f "Time: %e seconds\nMemory: %M KB" ./$(EXECUTABLE) $(ALGO) $(SIZE)

# Run single algorithm with time measurement
run: $(EXECUTABLE)
	@/usr/bin/time -f "Time: %e\nMemory: %M" ./$(EXECUTABLE) $(ALGO) $(SIZE) 2>&1

# Complete analysis - this is what you need for part 3
analyze: $(EXECUTABLE) process.sh
	@echo "$(GREEN)Starting complete algorithm analysis...$(NC)"
	@echo "$(YELLOW)This will take some time (testing multiple sizes with 100+ runs each)$(NC)"
	@chmod +x process.sh
	@./process.sh
	@echo "$(GREEN)Analysis complete! Generating plots...$(NC)"
	@make plots

# Generate plots using gnuplot
plots:
	@echo "$(YELLOW)Generating plots with gnuplot...$(NC)"
	@if command -v gnuplot >/dev/null 2>&1; then \
		gnuplot plot_time.gp && echo "$(GREEN)Generated: time_comparison.png$(NC)"; \
		gnuplot plot_memory.gp && echo "$(GREEN)Generated: memory_comparison.png$(NC)"; \
		gnuplot plot_combined.gp && echo "$(GREEN)Generated: combined_comparison.png$(NC)"; \
		echo "$(GREEN)All plots generated successfully!$(NC)"; \
	else \
		echo "$(RED)Error: gnuplot not found. Please install gnuplot.$(NC)"; \
		exit 1; \
	fi

# Create the bash script if it doesn't exist
process.sh:
	@echo "$(RED)Error: process.sh not found!$(NC)"
	@echo "Please create the bash script using the provided template."
	@exit 1

# Quick test with smaller dataset for debugging
quick_test: $(EXECUTABLE)
	@echo "$(YELLOW)Running quick test with smaller dataset...$(NC)"
	@for algo in merge quick heap; do \
		echo "Testing $$algo:"; \
		/usr/bin/time -f "  Time: %e seconds, Memory: %M KB" ./$(EXECUTABLE) $$algo 5000; \
		echo; \
	done

# Benchmark specific algorithm across different sizes
benchmark: $(EXECUTABLE)
	@echo "$(YELLOW)Benchmarking $(ALGO) across different input sizes...$(NC)"
	@for size in 1000 5000 10000 20000; do \
		echo "Size $$size:"; \
		/usr/bin/time -f "  Time: %e seconds, Memory: %M KB" ./$(EXECUTABLE) $(ALGO) $$size; \
		echo; \
	done

# Clean generated files
clean:
	@echo "$(YELLOW)Cleaning generated files...$(NC)"
	@rm -f $(EXECUTABLE)
	@rm -f *.png
	@rm -f *.gp
	@rm -rf processed_data/
	@rm -f output_*.txt
	@echo "$(GREEN)Clean complete!$(NC)"

# Display help
help:
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  all          - Compile all algorithms"
	@echo "  test         - Run single test (use ALGO=algorithm SIZE=number)"
	@echo "  analyze      - Run complete analysis and generate plots"
	@echo "  plots        - Generate plots from existing data"
	@echo "  quick_test   - Run quick test with smaller dataset"
	@echo "  benchmark    - Benchmark specific algorithm (use ALGO=algorithm)"
	@echo "  clean        - Clean all generated files"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "$(YELLOW)Examples:$(NC)"
	@echo "  make test ALGO=merge SIZE=15000"
	@echo "  make benchmark ALGO=quick"
	@echo "  make analyze    # This is what you need for part 3!"

# Install dependencies (Ubuntu/Debian)
install_deps:
	@echo "$(YELLOW)Installing dependencies...$(NC)"
	@sudo apt-get update
	@sudo apt-get install -y build-essential gnuplot bc
	@echo "$(GREEN)Dependencies installed!$(NC)"