CXX = g++
CXXFLAGS = -O2 -std=c++17
LOG_DIR = ./logs
REPEAT = 5   # number of runs for averaging

all: prob1 prob2 prob3

# Compile
prob1: prob1.cpp graph.h
	$(CXX) $(CXXFLAGS) -o prob1 prob1.cpp

prob2: prob2.cpp graph.h
	$(CXX) $(CXXFLAGS) -o prob2 prob2.cpp

prob3: prob3.cpp graph.h
	$(CXX) $(CXXFLAGS) -o prob3 prob3.cpp

# Run experiments
run: run_prob1 run_prob2 run_prob3

# ---------------- Problem 1: Graph Traversal ----------------
run_prob1: prob1
	mkdir -p $(LOG_DIR)
	# VARM: fixed N, vary M
	for m in 400 800 1600 3200 6400; do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARM,200,$$m,BFS,%M" ./prob1 VARM 200 $$m $$i bfs >> $(LOG_DIR)/prob1_varm.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,200,$$m,DFS_ITER,%M" ./prob1 VARM 200 $$m $$i dfs_iter >> $(LOG_DIR)/prob1_varm.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,200,$$m,DFS_REC,%M" ./prob1 VARM 200 $$m $$i dfs_rec >> $(LOG_DIR)/prob1_varm.log 2>&1; \
	  done; \
	done
	# VARN: fixed sparsity, vary N
	for n in 100 200 400 600 800 1000; do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARN,$$n,2,BFS,%M" ./prob1 VARN $$n 2 $$i bfs >> $(LOG_DIR)/prob1_varn.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARN,$$n,2,DFS_ITER,%M" ./prob1 VARN $$n 2 $$i dfs_iter >> $(LOG_DIR)/prob1_varn.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARN,$$n,2,DFS_REC,%M" ./prob1 VARN $$n 2 $$i dfs_rec >> $(LOG_DIR)/prob1_varn.log 2>&1; \
	  done; \
	done

# ---------------- Problem 2: Shortest Path ----------------
run_prob2: prob2
	mkdir -p $(LOG_DIR)
	for n in 200 400 600 800 1000; do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARM,$$n,400,DIJKSTRA,%M" ./prob2 VARM $$n 400 unweighted $$i dijkstra >> $(LOG_DIR)/prob2.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$$n,400,BFS_VARIANT,%M" ./prob2 VARM $$n 400 unweighted $$i bfs >> $(LOG_DIR)/prob2.log 2>&1; \
	  done; \
	done

# ---------------- Problem 3: SCC ----------------
run_prob3: prob3
	mkdir -p $(LOG_DIR)
	for n in 200 400 600 800 1000; do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARM,$$n,400,ALGO1,%M" ./prob3 VARM $$n 400 $$i algo1 >> $(LOG_DIR)/prob3.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$$n,400,ALGO2,%M" ./prob3 VARM $$n 400 $$i algo2 >> $(LOG_DIR)/prob3.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$$n,400,ALGO3,%M" ./prob3 VARM $$n 400 $$i algo3 >> $(LOG_DIR)/prob3.log 2>&1; \
	  done; \
	done

process: run
	bash process.sh

clean:
	rm -f prob1 prob2 prob3
	rm -rf $(LOG_DIR)
	rm -f *.dat *.png
