# GNUplot script for graph algorithm visualizations

# Set output format
set terminal pngcairo enhanced font 'Arial,12' size 1200,800

# Problem 1: Graph Traversal - VARM comparison
set output 'plots/prob1_varm_comparison.png'
set title 'Graph Traversal Algorithms - VARM Comparison'
set xlabel 'Number of Edges (m)'
set ylabel 'Time (microseconds)'
set key top left
set grid
plot 'results/processed/prob1_varm_bfs.dat' using 3:5 with linespoints title 'BFS' lw 2 pt 7, \
     'results/processed/prob1_varm_dfs_iter.dat' using 3:5 with linespoints title 'DFS Iterative' lw 2 pt 5, \
     'results/processed/prob1_varm_dfs_rec.dat' using 3:5 with linespoints title 'DFS Recursive' lw 2 pt 9

# Problem 1: Graph Traversal - VARN comparison
set output 'plots/prob1_varn_comparison.png'
set title 'Graph Traversal Algorithms - VARN Comparison'
set xlabel 'Number of Nodes (n)'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob1_varn_bfs.dat' using 2:5 with linespoints title 'BFS' lw 2 pt 7, \
     'results/processed/prob1_varn_dfs_iter.dat' using 2:5 with linespoints title 'DFS Iterative' lw 2 pt 5, \
     'results/processed/prob1_varn_dfs_rec.dat' using 2:5 with linespoints title 'DFS Recursive' lw 2 pt 9

# Problem 2: Shortest Path - Unweighted
set output 'plots/prob2_unweighted.png'
set title 'Shortest Path Algorithms - Unweighted Graphs'
set xlabel 'Number of Edges (m)'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob2_varm_unweighted_dijkstra.dat' using 3:6 with linespoints title 'Dijkstra' lw 2 pt 7, \
     'results/processed/prob2_varm_unweighted_bfs.dat' using 3:6 with linespoints title 'BFS' lw 2 pt 5

# Problem 2: Shortest Path - 0-1 Weighted
set output 'plots/prob2_01weighted.png'
set title 'Shortest Path Algorithms - 0-1 Weighted Graphs'
set xlabel 'Number of Edges (m)'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob2_varm_01_dijkstra.dat' using 3:6 with linespoints title 'Dijkstra' lw 2 pt 7, \
     'results/processed/prob2_varm_01_bfs.dat' using 3:6 with linespoints title '0-1 BFS' lw 2 pt 5

# Problem 2: Shortest Path - Weighted BFS
set output 'plots/prob2_wbfs_comparison.png'
set title 'Weighted BFS Performance vs Dijkstra'
set xlabel 'Number of Edges (m)'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob2_varm_wbfs_5_dijkstra.dat' using 3:6 with linespoints title 'Dijkstra' lw 2 pt 7, \
     'results/processed/prob2_varm_wbfs_5_bfs.dat' using 3:6 with linespoints title 'WBFS (c=5)' lw 2 pt 5

# Problem 3: SCC - VARM comparison
set output 'plots/prob3_varm_comparison.png'
set title 'SCC Algorithms - VARM Comparison'
set xlabel 'Number of Edges (m)'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob3_varm_algo1.dat' using 3:5 with linespoints title 'Algorithm 1 (DFS)' lw 2 pt 7, \
     'results/processed/prob3_varm_algo2.dat' using 3:5 with linespoints title 'Algorithm 2 (BFS)' lw 2 pt 5, \
     'results/processed/prob3_varm_algo3.dat' using 3:5 with linespoints title 'Algorithm 3 (Kosaraju)' lw 2 pt 9

# Problem 3: SCC - VARN comparison
set output 'plots/prob3_varn_comparison.png'
set title 'SCC Algorithms - VARN Comparison'
set xlabel 'Number of Nodes (n)'
set ylabel 'Time (microseconds)'
plot 'results/processed/prob3_varn_algo1.dat' using 2:5 with linespoints title 'Algorithm 1 (DFS)' lw 2 pt 7, \
     'results/processed/prob3_varn_algo2.dat' using 2:5 with linespoints title 'Algorithm 2 (BFS)' lw 2 pt 5, \
     'results/processed/prob3_varn_algo3.dat' using 2:5 with linespoints title 'Algorithm 3 (Kosaraju)' lw 2 pt 9