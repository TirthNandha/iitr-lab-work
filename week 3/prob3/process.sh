#!/bin/bash

echo "Starting sorting algorithm analysis..."

# Settings
sizes=(1000 5000 10000 15000 20000 30000)
algorithms=(merge quick heap bubble selection)
runs=20

mkdir -p results

echo "Size Merge Quick Heap Bubble Selection" > results/time_data.txt
echo "Size Merge Quick Heap Bubble Selection" > results/memory_data.txt

for size in "${sizes[@]}"; do
    echo "Testing size: $size"
    
    time_line="$size"
    memory_line="$size"
    
    for algo in "${algorithms[@]}"; do
        echo "  Testing $algo..."
        
        total_time=0
        total_memory=0
        
        for ((i=1; i<=runs; i++)); do
            output=$(./sorting_test $algo $size)
            time=$(echo "$output" | grep "Time:" | cut -d' ' -f2)
            memory=$(echo "$output" | grep "Memory:" | cut -d' ' -f2)
            
            total_time=$(echo "$total_time + $time" | bc -l)
            total_memory=$((total_memory + memory))
        done
        
        avg_time=$(echo "scale=4; $total_time / $runs" | bc -l)
        avg_memory=$((total_memory / runs))
        
        time_line="$time_line $avg_time"
        memory_line="$memory_line $avg_memory"
        
        echo "    Average time: $avg_time seconds"
    done
    
    echo "$time_line" >> results/time_data.txt
    echo "$memory_line" >> results/memory_data.txt
done

echo "Data collection complete!"

echo "Creating plot scripts..."

cat > plot_time.gnu << 'EOF'
set terminal png
set output 'time_comparison.png'
set title 'Sorting Algorithm Time Comparison'
set xlabel 'Input Size'
set ylabel 'Time (seconds)'
set grid

plot 'results/time_data.txt' using 1:2 with linespoints title 'Merge', \
     '' using 1:3 with linespoints title 'Quick', \
     '' using 1:4 with linespoints title 'Heap', \
     '' using 1:5 with linespoints title 'Bubble', \
     '' using 1:6 with linespoints title 'Selection'
EOF

cat > plot_memory.gnu << 'EOF'
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
EOF

echo "Scripts created! Run 'gnuplot plot_time.gnu' and 'gnuplot plot_memory.gnu' to create graphs."