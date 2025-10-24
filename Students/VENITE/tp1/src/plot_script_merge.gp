set terminal pngcairo size 800,600
set output 'merge_sort_performance.png'
set title 'Merge Sort Performance'
set xlabel 'Number of elements (N)'
set ylabel 'Execution time (seconds)'
set logscale xy
set grid
plot 'merge_times.dat' with linespoints title 'Merge Sort'
