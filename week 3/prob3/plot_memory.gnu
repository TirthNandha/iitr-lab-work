set terminal png
set output 'memory_comparison.png'
set title 'Sorting Algorithm Memory Usage'
set xlabel 'Input Size'
set ylabel 'Memory (KB)'
set grid

plot 'results/memory_data.txt' using 1:2 with linespoints title 'Merge', \
     '' using 1:3 with linespoints title 'Quick', \
     '' using 1:4 with linespoints title 'Heap', \
     '' using 1:5 with linespoints title 'Bubble', \
     '' using 1:6 with linespoints title 'Selection'
