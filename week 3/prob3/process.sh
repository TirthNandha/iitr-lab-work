#!/bin/bash

for file in *_log.txt; do
    if [[ ! -f "$file" ]]; then
        echo "No log file found: $file"
        continue
    fi

    algo="${file%%_log.txt}"
    sum_time=0
    sum_mem=0
    count=0

    while read -r time mem; do
        sum_time=$(echo "$sum_time + $time" | bc -l)
        sum_mem=$(echo "$sum_mem + $mem" | bc -l)
        count=$((count + 1))
    done < "$file"

    if [ "$count" -eq 0 ]; then
        echo "No valid entries in $file"
        continue
    fi

    avg_time=$(echo "$sum_time / $count" | bc -l)
    avg_mem=$(echo "$sum_mem / $count" | bc -l)

    echo "$avg_time $avg_mem" > "${algo}_summary.txt"
done
