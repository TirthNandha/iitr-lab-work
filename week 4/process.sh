#!/bin/bash

# Create processed results directory
mkdir -p results/processed

# Function to average results
average_results() {
    local input_file=$1
    local output_file=$2
    local problem=$3
    
    echo "Processing $input_file -> $output_file"
    
    # Process results based on problem type
    case $problem in
        "prob1")
            # Format: GRAPH_TRAVERSAL,graph_type,n,m,algorithm,time
            awk -F',' '
            {
                key = $2 "," $3 "," $4 "," $5
                sum[key] += $6
                count[key]++
            }
            END {
                for (k in sum) {
                    split(k, parts, ",")
                    print parts[1] "," parts[2] "," parts[3] "," parts[4] "," sum[k]/count[k]
                }
            }' $input_file | sort -t',' -k1,1 -k2,2n -k3,3n -k4,4 > $output_file
            ;;
            
        "prob2")
            # Format: SHORTEST_PATH,graph_type,n,m,weight_type,algorithm,time
            awk -F',' '
            {
                key = $2 "," $3 "," $4 "," $5 "," $6
                sum[key] += $7
                count[key]++
            }
            END {
                for (k in sum) {
                    split(k, parts, ",")
                    print parts[1] "," parts[2] "," parts[3] "," parts[4] "," parts[5] "," sum[k]/count[k]
                }
            }' $input_file | sort -t',' -k1,1 -k2,2n -k3,3n -k4,4 -k5,5 > $output_file
            ;;
            
        "prob3")
            # Format: SCC,graph_type,n,m,algorithm,time
            awk -F',' '
            {
                key = $2 "," $3 "," $4 "," $5
                sum[key] += $6
                count[key]++
            }
            END {
                for (k in sum) {
                    split(k, parts, ",")
                    print parts[1] "," parts[2] "," parts[3] "," parts[4] "," sum[k]/count[k]
                }
            }' $input_file | sort -t',' -k1,1 -k2,2n -k3,3n -k4,4 > $output_file
            ;;
    esac
}

# Process each problem's results
if [ -f "results/prob1_raw.txt" ]; then
    average_results "results/prob1_raw.txt" "results/processed/prob1_avg.txt" "prob1"
    
    # Split by graph type and algorithm for plotting
    grep "VARM" results/processed/prob1_avg.txt | grep "BFS" > results/processed/prob1_varm_bfs.txt
    grep "VARM" results/processed/prob1_avg.txt | grep "DFS_ITER" > results/processed/prob1_varm_dfs_iter.txt
    grep "VARM" results/processed/prob1_avg.txt | grep "DFS_REC" > results/processed/prob1_varm_dfs_rec.txt
    
    grep "VARN" results/processed/prob1_avg.txt | grep "BFS" > results/processed/prob1_varn_bfs.txt
    grep "VARN" results/processed/prob1_avg.txt | grep "DFS_ITER" > results/processed/prob1_varn_dfs_iter.txt
    grep "VARN" results/processed/prob1_avg.txt | grep "DFS_REC" > results/processed/prob1_varn_dfs_rec.txt
fi

if [ -f "results/prob2_raw.txt" ]; then
    average_results "results/prob2_raw.txt" "results/processed/prob2_avg.txt" "prob2"
    
    # Split by weight type and algorithm
    for weight in unweighted 01 wbfs_5 wbfs_10; do
        grep "VARM.*$weight" results/processed/prob2_avg.txt | grep "DIJKSTRA" > results/processed/prob2_varm_${weight}_dijkstra.txt
        grep "VARM.*$weight" results/processed/prob2_avg.txt | grep "BFS_VARIANT" > results/processed/prob2_varm_${weight}_bfs.txt
    done
fi

if [ -f "results/prob3_raw.txt" ]; then
    average_results "results/prob3_raw.txt" "results/processed/prob3_avg.txt" "prob3"
    
    # Split by graph type and algorithm
    grep "VARM" results/processed/prob3_avg.txt | grep "ALGO1_DFS" > results/processed/prob3_varm_algo1.txt
    grep "VARM" results/processed/prob3_avg.txt | grep "ALGO2_BFS" > results/processed/prob3_varm_algo2.txt
    grep "VARM" results/processed/prob3_avg.txt | grep "ALGO3_KOSARAJU" > results/processed/prob3_varm_algo3.txt
    
    grep "VARN" results/processed/prob3_avg.txt | grep "ALGO1_DFS" > results/processed/prob3_varn_algo1.txt
    grep "VARN" results/processed/prob3_avg.txt | grep "ALGO2_BFS" > results/processed/prob3_varn_algo2.txt
    grep "VARN" results/processed/prob3_avg.txt | grep "ALGO3_KOSARAJU" > results/processed/prob3_varn_algo3.txt
fi

# Convert CSV files to space-separated format for GNUplot
echo "Converting data files to GNUplot format..."
for file in results/processed/*.txt; do
    if [ -f "$file" ]; then
        sed 's/,/ /g' "$file" > "${file%.txt}.dat"
    fi
done

echo "Processing complete!"