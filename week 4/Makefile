CXX = g++
CXXFLAGS = -O2 -std=c++17
LOG_DIR = ./logs
REPEAT = 5   # number of runs for averaging

# Graph parameters - easily configurable
FIXED_N = 1000     # Fixed N for VARM experiments
FIXED_M = 500     # Fixed M for VARN experiments  
VARM_M_VALUES = 400 800 1600 3200 6400      # M values for VARM (varying edges)
VARN_N_VALUES = 100 200 400 600 800 1000    # N values for VARN (varying nodes)
VARN_SPARSITY = 2  # Sparsity option for VARN (1=2n, 2=nlogn, 3=n√n, 4=n(n-1)/2)

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
	for m in $(VARM_M_VALUES); do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARM,$(FIXED_N),$$m,BFS,%M" ./prob1 VARM $(FIXED_N) $$m $$i bfs >> $(LOG_DIR)/prob1_varm.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$(FIXED_N),$$m,DFS_ITER,%M" ./prob1 VARM $(FIXED_N) $$m $$i dfs_iter >> $(LOG_DIR)/prob1_varm.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$(FIXED_N),$$m,DFS_REC,%M" ./prob1 VARM $(FIXED_N) $$m $$i dfs_rec >> $(LOG_DIR)/prob1_varm.log 2>&1; \
	  done; \
	done
	# VARN: fixed sparsity, vary N
	for n in $(VARN_N_VALUES); do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARN,$$n,$(VARN_SPARSITY),BFS,%M" ./prob1 VARN $$n $(VARN_SPARSITY) $$i bfs >> $(LOG_DIR)/prob1_varn.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARN,$$n,$(VARN_SPARSITY),DFS_ITER,%M" ./prob1 VARN $$n $(VARN_SPARSITY) $$i dfs_iter >> $(LOG_DIR)/prob1_varn.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARN,$$n,$(VARN_SPARSITY),DFS_REC,%M" ./prob1 VARN $$n $(VARN_SPARSITY) $$i dfs_rec >> $(LOG_DIR)/prob1_varn.log 2>&1; \
	  done; \
	done

# ---------------- Problem 2: Shortest Path ----------------
run_prob2: prob2
	mkdir -p $(LOG_DIR)
	for n in $(VARN_N_VALUES); do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARM,$$n,$(FIXED_M),DIJKSTRA,%M" ./prob2 VARM $$n $(FIXED_M) unweighted $$i dijkstra >> $(LOG_DIR)/prob2.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$$n,$(FIXED_M),BFS_VARIANT,%M" ./prob2 VARM $$n $(FIXED_M) unweighted $$i bfs >> $(LOG_DIR)/prob2.log 2>&1; \
	  done; \
	done

# ---------------- Problem 3: SCC ----------------
run_prob3: prob3
	mkdir -p $(LOG_DIR)
	for n in $(VARN_N_VALUES); do \
	  for i in $$(seq 1 $(REPEAT)); do \
	    /usr/bin/time -f "MEMORY,VARM,$$n,$(FIXED_M),ALGO1,%M" ./prob3 VARM $$n $(FIXED_M) $$i algo1 >> $(LOG_DIR)/prob3.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$$n,$(FIXED_M),ALGO2,%M" ./prob3 VARM $$n $(FIXED_M) $$i algo2 >> $(LOG_DIR)/prob3.log 2>&1; \
	    /usr/bin/time -f "MEMORY,VARM,$$n,$(FIXED_M),ALGO3,%M" ./prob3 VARM $$n $(FIXED_M) $$i algo3 >> $(LOG_DIR)/prob3.log 2>&1; \
	  done; \
	done

process: run
	bash process.sh

clean:
	rm -f prob1 prob2 prob3
	rm -rf $(LOG_DIR)
	rm -f *.dat *.png
