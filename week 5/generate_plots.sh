#!/bin/bash

# Check if gnuplot is installed
if ! command -v gnuplot &> /dev/null; then
    echo "Error: gnuplot not installed"
    exit 1
fi

# Check if data files exist
if [ ! -f "results/test1_thread_scaling.csv" ] || [ ! -f "results/test2_size_scaling.csv" ]; then
    echo "Error: Data files not found. Run 'make perf' first."
    exit 1
fi

# Generate plots
echo "Generating performance graphs..."
gnuplot plot_performance.gnuplot 2>/dev/null

# Check if plots were created
if [ -f "thread_scaling.png" ] && [ -f "size_scaling.png" ]; then
    echo "✓ Graphs generated: thread_scaling.png, size_scaling.png"
else
    echo "Error: Failed to generate graphs"
    exit 1
fi