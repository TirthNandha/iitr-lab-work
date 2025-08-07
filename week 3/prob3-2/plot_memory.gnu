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
