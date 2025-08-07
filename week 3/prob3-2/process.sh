#!/bin/bash

# Process script for sorting algorithm analysis
# This script runs multiple algorithms with different input sizes and processes the results

echo "========================================"
echo "    Sorting Algorithm Analysis Tool    "
echo "========================================"

# Configuration
INPUT_SIZES=(1000 5000 10000 15000 20000 30000)  # Input sizes to test
ALGORITHMS=(merge quick randomized_quick heap bubble selection)  # Algorithms to test
NUM_RUNS=50  # Number of runs per algorithm per size (professor wants 100+, start with 50 for testing)

# Create results directory
mkdir -p results

# Initialize data files with headers
echo "# InputSize Merge Quick RandomizedQuick Heap Bubble Selection" > results/time_data.txt
echo "# InputSize Merge Quick RandomizedQuick Heap Bubble Selection" > results/memory_data.txt

echo "Configuration:"
echo "  Input sizes: ${INPUT_SIZES[*]}"
echo "  Algorithms: ${ALGORITHMS[*]}"
echo "  Runs per test: $NUM_RUNS"
echo "  Total tests: $((${#INPUT_SIZES[@]} * ${#ALGORITHMS[@]} * NUM_RUNS))"
echo

# Check if sorting_test executable exists
if [ ! -f "./sorting_test" ]; then
    echo "Error: sorting_test executable not found!"
    echo "Please run 'make all' first to compile the program."
    exit 1
fi

echo "Starting analysis..."
echo

# Process each input size
for size in "${INPUT_SIZES[@]}"; do
    echo "Processing input size: $size"
    
    # Initialize result arrays for this size
    declare -A total_time
    declare -A total_memory
    declare -A valid_runs
    
    # Initialize totals
    for algo in "${ALGORITHMS[@]}"; do
        total_time[$algo]=0
        total_memory[$algo]=0
        valid_runs[$algo]=0
    done
    
    # Run each algorithm multiple times
    for algo in "${ALGORITHMS[@]}"; do
        echo "  Testing $algo..."
        
        for ((run=1; run<=NUM_RUNS; run++)); do
            # Run the sorting algorithm and capture output
            output=$(./sorting_test $algo $size 2>/dev/null)
            
            # Extract time value
            time_val=$(echo "$output" | grep "Time:" | cut -d' ' -f2)
            
            # Extract memory value  
            memory_val=$(echo "$output" | grep "Memory:" | cut -d' ' -f2)
            
            # Add to totals if values are valid numbers
            if [[ "$time_val" =~ ^[0-9]*\.?[0-9]+$ ]]; then
                total_time[$algo]=$(echo "${total_time[$algo]} + $time_val" | bc -l)
                valid_runs[$algo]=$((${valid_runs[$algo]} + 1))
            fi
            
            if [[ "$memory_val" =~ ^[0-9]+$ ]]; then
                total_memory[$algo]=$((${total_memory[$algo]} + memory_val))
            fi
            
            # Show progress every 10 runs
            if ((run % 10 == 0)); then
                echo "    Progress: $run/$NUM_RUNS runs completed"
            fi
        done
        
        echo "    Completed $algo: ${valid_runs[$algo]} valid runs out of $NUM_RUNS"
    done
    
    # Calculate averages and prepare data for output
    time_line="$size"
    memory_line="$size"
    
    for algo in "${ALGORITHMS[@]}"; do
        if ((${valid_runs[$algo]} > 0)); then
            avg_time=$(echo "scale=6; ${total_time[$algo]} / ${valid_runs[$algo]}" | bc -l)
            avg_memory=$((${total_memory[$algo]} / ${valid_runs[$algo]}))
        else
            avg_time=0
            avg_memory=0
            echo "  Warning: No valid runs for $algo"
        fi
        
        time_line="$time_line $avg_time"
        memory_line="$memory_line $avg_memory"
        
        echo "  $algo averages: ${avg_time}s, ${avg_memory}KB"
    done
    
    # Write results to data files
    echo "$time_line" >> results/time_data.txt
    echo "$memory_line" >> results/memory_data.txt
    
    # Clean up arrays
    unset total_time total_memory valid_runs
    
    echo "  ✓ Size $size completed"
    echo
done

echo "========================================"
echo "Data processing completed successfully!"
echo "========================================"
echo "Generated files:"
echo "  📊 results/time_data.txt"
echo "  📊 results/memory_data.txt"
echo

# Create gnuplot scripts
echo "Creating gnuplot scripts..."

# Time comparison plot
cat > plot_time.gnu << 'EOF'
set terminal png size 1200,800
set output 'time_comparison.png'
set title 'Sorting Algorithms Time Comparison'
set xlabel 'Input Size'
set ylabel 'Average Time (seconds)'
set grid
set key top left

plot 'results/time_data.txt' using 1:2 with linespoints linewidth 2 pointtype 7 title 'Merge Sort', \
     '' using 1:3 with linespoints linewidth 2 pointtype 5 title 'Quick Sort', \
     '' using 1:4 with linespoints linewidth 2 pointtype 9 title 'Randomized Quick', \
     '' using 1:5 with linespoints linewidth 2 pointtype 11 title 'Heap Sort', \
     '' using 1:6 with linespoints linewidth 2 pointtype 13 title 'Bubble Sort', \
     '' using 1:7 with linespoints linewidth 2 pointtype 15 title 'Selection Sort'
EOF

# Memory comparison plot
cat > plot_memory.gnu << 'EOF'
set terminal png size 1200,800
set output 'memory_comparison.png'
set title 'Sorting Algorithms Memory Usage Comparison'
set xlabel 'Input Size'
set ylabel 'Average Memory Usage (KB)'
set grid
set key top left

plot 'results/memory_data.txt' using 1:2 with linespoints linewidth 2 pointtype 7 title 'Merge Sort', \
     '' using 1:3 with linespoints linewidth 2 pointtype 5 title 'Quick Sort', \
     '' using 1:4 with linespoints linewidth 2 pointtype 9 title 'Randomized Quick', \
     '' using 1:5 with linespoints linewidth 2 pointtype 11 title 'Heap Sort', \
     '' using 1:6 with linespoints linewidth 2 pointtype 13 title 'Bubble Sort', \
     '' using 1:7 with linespoints linewidth 2 pointtype 15 title 'Selection Sort'
EOF

# Combined comparison with log scale for time
cat > plot_combined.gnu << 'EOF'
set terminal png size 1400,1000
set output 'combined_analysis.png'

set multiplot layout 2,1 title "Complete Sorting Algorithm Analysis"

# Time plot with log scale (top)
set title 'Time Comparison (Log Scale)'
set xlabel 'Input Size'
set ylabel 'Average Time (seconds)'
set logscale y
set grid
set key top left

plot 'results/time_data.txt' using 1:2 with linespoints linewidth 2 pointtype 7 title 'Merge Sort', \
     '' using 1:3 with linespoints linewidth 2 pointtype 5 title 'Quick Sort', \
     '' using 1:4 with linespoints linewidth 2 pointtype 9 title 'Randomized Quick', \
     '' using 1:5 with linespoints linewidth 2 pointtype 11 title 'Heap Sort', \
     '' using 1:6 with linespoints linewidth 2 pointtype 13 title 'Bubble Sort', \
     '' using 1:7 with linespoints linewidth 2 pointtype 15 title 'Selection Sort'

# Memory plot (bottom)
unset logscale y
set title 'Memory Usage Comparison'
set xlabel 'Input Size'
set ylabel 'Average Memory Usage (KB)'

plot 'results/memory_data.txt' using 1:2 with linespoints linewidth 2 pointtype 7 title 'Merge Sort', \
     '' using 1:3 with linespoints linewidth 2 pointtype 5 title 'Quick Sort', \
     '' using 1:4 with linespoints linewidth 2 pointtype 9 title 'Randomized Quick', \
     '' using 1:5 with linespoints linewidth 2 pointtype 11 title 'Heap Sort', \
     '' using 1:6 with linespoints linewidth 2 pointtype 13 title 'Bubble Sort', \
     '' using 1:7 with linespoints linewidth 2 pointtype 15 title 'Selection Sort'

unset multiplot
EOF

echo "✓ Gnuplot scripts created:"
echo "  📈 plot_time.gnu"
echo "  📈 plot_memory.gnu"
echo "  📈 plot_combined.gnu"
echo

echo "To generate plots, run:"
echo "  gnuplot plot_time.gnu"
echo "  gnuplot plot_memory.gnu"
echo "  gnuplot plot_combined.gnu"
echo
echo "Or simply run: make plots"
echo

echo "Analysis complete! 🎉"