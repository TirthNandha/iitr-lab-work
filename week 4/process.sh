#!/bin/bash
set -e
LOG_DIR=./logs

# Function to average columns with awk
avg_col() {
  awk -F',' -v col=$1 '{
    sum[$5]+=$col; count[$5]++
  } END {
    for (alg in sum) {
      print alg, sum[alg]/count[alg]
    }
  }' $2 | sort
}

# ---------- Problem 1: Graph Traversal ----------
# Extract time data from program output and memory data from /usr/bin/time
grep "GRAPH_TRAVERSAL" $LOG_DIR/prob1_varm.log > p1_varm_time.tmp
grep "GRAPH_TRAVERSAL" $LOG_DIR/prob1_varn.log > p1_varn_time.tmp
grep "MEMORY" $LOG_DIR/prob1_varm.log > p1_varm_mem.tmp
grep "MEMORY" $LOG_DIR/prob1_varn.log > p1_varn_mem.tmp

# Time averages (convert microseconds to seconds)
awk -F',' '{
  sum[$5]+=$6/1000000; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p1_varm_time.tmp | sort > prob1_varm_time.dat

awk -F',' '{
  sum[$5]+=$6/1000000; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p1_varn_time.tmp | sort > prob1_varn_time.dat

# Memory averages by algorithm
awk -F',' '{
  sum[$5]+=$6; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p1_varm_mem.tmp | sort > prob1_varm_mem.dat

awk -F',' '{
  sum[$5]+=$6; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p1_varn_mem.tmp | sort > prob1_varn_mem.dat

gnuplot -persist <<EOF
set terminal pngcairo size 900,600
set output "prob1_time.png"
set title "Graph Traversal Time (VARM vs VARN)"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.6
set ylabel "Time (s)"
plot "prob1_varm_time.dat" using 2:xtic(1) title "VARM", \
     "prob1_varn_time.dat" using 2:xtic(1) title "VARN"

set output "prob1_mem.png"
set title "Graph Traversal Memory (VARM vs VARN)"
set ylabel "Memory (KB)"
plot "prob1_varm_mem.dat" using 2:xtic(1) title "VARM", \
     "prob1_varn_mem.dat" using 2:xtic(1) title "VARN"
EOF

# ---------- Problem 2: Shortest Path ----------
grep "SHORTEST_PATH" $LOG_DIR/prob2.log > p2_time.tmp
grep "MEMORY" $LOG_DIR/prob2.log > p2_mem.tmp

awk -F',' '{
  sum[$6]+=$7/1000000; count[$6]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p2_time.tmp | sort > prob2_time.dat

awk -F',' '{
  sum[$5]+=$6; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p2_mem.tmp | sort > prob2_mem.dat

gnuplot -persist <<EOF
set terminal pngcairo size 900,600
set output "prob2_time.png"
set title "Shortest Path Time"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.6
set ylabel "Time (s)"
set yrange [0:*]
set format y "%.1e"
plot "prob2_time.dat" using 2:xtic(1) title "Algorithms"

set output "prob2_mem.png"
set title "Shortest Path Memory"
set ylabel "Memory (KB)"
set format y "%.0f"
plot "prob2_mem.dat" using 2:xtic(1) title "Algorithms"
EOF

# ---------- Problem 3: SCC ----------
grep "SCC" $LOG_DIR/prob3.log > p3_time.tmp
grep "MEMORY" $LOG_DIR/prob3.log > p3_mem.tmp

awk -F',' '{
  sum[$5]+=$6/1000000; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p3_time.tmp | sort > prob3_time.dat

awk -F',' '{
  sum[$5]+=$6; count[$5]++
} END {
  for (alg in sum) {
    print alg, sum[alg]/count[alg]
  }
}' p3_mem.tmp | sort > prob3_mem.dat

gnuplot -persist <<EOF
set terminal pngcairo size 900,600
set output "prob3_time.png"
set title "SCC Algorithms Time"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.6
set ylabel "Time (s)"
plot "prob3_time.dat" using 2:xtic(1) title "Algorithms"

set output "prob3_mem.png"
set title "SCC Algorithms Memory"
set ylabel "Memory (KB)"
plot "prob3_mem.dat" using 2:xtic(1) title "Algorithms"
EOF

# Cleanup
rm -f p1_varm_time.tmp p1_varn_time.tmp p1_varm_mem.tmp p1_varn_mem.tmp
rm -f p2_time.tmp p2_mem.tmp p3_time.tmp p3_mem.tmp

echo "✅ Plots generated: prob1_time.png prob1_mem.png prob2_time.png prob2_mem.png prob3_time.png prob3_mem.png"
