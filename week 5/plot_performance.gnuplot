#!/usr/bin/gnuplot

# Set output format and data format
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set datafile separator ','

# PLOT 1: Thread Scaling Performance
set output 'thread_scaling.png'
set title 'Thread Scaling Performance (N = 1,000,000 elements)'
set xlabel 'Number of Threads (M)'
set ylabel 'Execution Time (ms)'
set grid
set key top right

# Style for the line
set style line 1 lc rgb '#0060ad' lt 1 lw 3 pt 7 ps 1.5

# Plot thread scaling data
plot 'results/test1_thread_scaling.csv' using 2:3 skip 1 with linespoints ls 1 title 'Execution Time'

# PLOT 2: Problem Size Scaling Performance
set output 'size_scaling.png'
set title 'Problem Size Scaling Performance (M = 4 threads)'
set xlabel 'Number of Elements (N)'
set ylabel 'Execution Time (ms)'
set grid
set key top left

# Use log scale for x-axis since values span orders of magnitude
set logscale x
set xtics (10, 100, 1000, 10000, 100000)
set format x "%.0f"

# Style for the line
set style line 1 lc rgb '#9333ea' lt 1 lw 3 pt 7 ps 1.5

# Plot size scaling data
plot 'results/test2_size_scaling.csv' using 1:3 skip 1 with linespoints ls 1 title 'Execution Time'

print "Graphs generated successfully!"
print "Generated files:"
print "  - thread_scaling.png"
print "  - size_scaling.png"