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
