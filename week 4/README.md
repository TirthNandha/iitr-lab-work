# Graph Algorithms Performance Analysis

This project implements and compares different graph algorithms for three problems:
1. Graph Traversal (BFS, DFS iterative, DFS recursive)
2. Shortest Path (Dijkstra vs BFS variants)
3. Strongly Connected Components (3 different algorithms)

## Project Structure

```
week 4/
├── graph.h          # Graph data structure and generation utilities
├── prob1.cpp        # Problem 1: Graph Traversal
├── prob2.cpp        # Problem 2: Shortest Path
├── prob3.cpp        # Problem 3: Strongly Connected Components
├── Makefile         # Build and experiment automation
├── process.sh       # Result processing script
├── plot.gnu         # GNUplot visualization script
├── results/         # Raw and processed results (created during execution)
└── plots/           # Generated plots (created during execution)
```

## Requirements

- C++ compiler with C++11 support (g++)
- GNU Make
- GNUplot
- Bash shell
- /usr/bin/time command

## How to Execute

### Quick Start (Run all experiments)

```bash
# 1. Compile all programs
make all

# 2. Run all experiments (this will take some time)
make experiments

# 3. Process results and generate plots
make process
```

### Step-by-Step Execution

#### 1. Compile the programs
```bash
make all
```

#### 2. Run individual problems

**Problem 1 - Graph Traversal:**
```bash
# VARM (Variable edges, fixed nodes)
./prob1 VARM 500 1000 12345

# VARN (Variable nodes, fixed sparsity)
# Sparsity: 1=2n, 2=nlogn, 3=n√n, 4=n(n-1)/2
./prob1 VARN 200 1 12345
```

**Problem 2 - Shortest Path:**
```bash
# Unweighted graph
./prob2 VARM 500 1000 unweighted 12345

# 0-1 weighted graph
./prob2 VARM 500 1000 01 12345

# Weighted BFS with max weight c
./prob2 VARM 500 1000 wbfs_5 12345
./prob2 VARM 500 1000 wbfs_10 12345
```

**Problem 3 - Strongly Connected Components:**
```bash
# VARM (directed graph)
./prob3 VARM 500 2000 12345

# VARN
./prob3 VARN 300 2 12345
```

#### 3. Run batch experiments
```bash
# Run all experiments for a specific problem
make run_prob1
make run_prob2
make run_prob3
```

#### 4. Process results
```bash
# Make sure process.sh is executable
chmod +x process.sh

# Process raw results into averaged data
./process.sh
```

#### 5. Generate plots
```bash
# Generate all plots using GNUplot
gnuplot plot.gnu
```

## Understanding the Output

### Command Line Arguments

All programs follow a similar pattern:
- `graph_type`: VARM (variable edges) or VARN (variable nodes)
- `n`: Number of nodes
- `m_or_sparsity`: For VARM, it's the number of edges. For VARN, it's the sparsity option (1-4)
- `seed`: Random seed for reproducible results

### Output Format

Programs output CSV-formatted results:
```
PROBLEM_TYPE,graph_type,n,m,algorithm,time_microseconds
```

Example:
```
GRAPH_TRAVERSAL,VARM,500,1000,BFS,2345
GRAPH_TRAVERSAL,VARM,500,1000,DFS_ITER,2156
GRAPH_TRAVERSAL,VARM,500,1000,DFS_REC,2089
```

### Generated Plots

The plots directory will contain:
- `prob1_varm_n*.png`: Graph traversal with fixed nodes, varying edges
- `prob1_varn_*.png`: Graph traversal with varying nodes, fixed sparsity
- `prob2_*.png`: Shortest path algorithm comparisons
- `prob3_*.png`: SCC algorithm comparisons

## Experiment Parameters

The Makefile is configured to:
- Test multiple node sizes: 100, 200, ..., 1000 for VARN
- Test node sizes 200, 500, 1000 for VARM
- Vary edges from 2n to n(n-1)/2 for VARM
- Run 5 iterations per configuration and average results
- Use random seeds for reproducibility

## Clean Up

```bash
# Remove compiled binaries and all results
make clean
```

## Troubleshooting

1. **Permission denied for process.sh**: Run `chmod +x process.sh`
2. **GNUplot not found**: Install with `sudo apt-get install gnuplot`
3. **Out of memory**: Reduce node sizes in Makefile or run experiments individually
4. **No plots generated**: Check if results/processed/ directory has data files

## Analysis Tips

1. Compare algorithm performance across different graph densities
2. Look for crossover points where one algorithm becomes better than another
3. Observe how performance scales with graph size
4. Note the impact of graph structure (sparse vs dense) on each algorithm

## Report Guidelines

When analyzing results, consider:
- Time complexity vs actual performance
- Memory usage patterns
- Effect of graph density on each algorithm
- Why certain algorithms perform better in specific scenarios
- Trade-offs between iterative and recursive approaches