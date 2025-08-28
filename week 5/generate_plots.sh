echo "Generating performance graphs..."
gnuplot plot_performance.gnuplot 2>/dev/null
echo "Graphs generated: thread_scaling.png, size_scaling.png"