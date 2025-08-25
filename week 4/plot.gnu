# Very simple GNUplot script
set terminal png size 800,600
set grid

# Problem 1: Graph Traversal Comparison
set output 'plots/traversal_comparison.png'
set title 'Graph Traversal Algorithms Performance'
set xlabel 'Number of Edges'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob1_bfs.dat' using 4:6 with linespoints title 'BFS', \
     'results/processed/prob1_dfs_iter.dat' using 4:6 with linespoints title 'DFS Iterative', \
     'results/processed/prob1_dfs_rec.dat' using 4:6 with linespoints title 'DFS Recursive'

# Problem 2: Shortest Path Comparison
set output 'plots/shortest_path_comparison.png'
set title 'Shortest Path Algorithms Performance'
set xlabel 'Number of Edges'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob2_dijkstra.dat' using 4:7 with linespoints title 'Dijkstra', \
     'results/processed/prob2_bfs.dat' using 4:7 with linespoints title 'BFS'

# Problem 3: SCC Comparison
set output 'plots/scc_comparison.png'
set title 'Strongly Connected Components Algorithms Performance'
set xlabel 'Number of Edges'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob3_algo1.dat' using 4:6 with linespoints title 'Algorithm 1', \
     'results/processed/prob3_algo2.dat' using 4:6 with linespoints title 'Algorithm 2', \
     'results/processed/prob3_algo3.dat' using 4:6 with linespoints title 'Algorithm 3'