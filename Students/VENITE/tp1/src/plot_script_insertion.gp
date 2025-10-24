set terminal pngcairo size 800,600
set output 'insertion_sort_performance.png'
set title 'Insertion Sort Performance'
set xlabel 'Number of elements (N)'
set ylabel 'Execution time (seconds)'
set logscale xy
set grid
plot 'insertion_times.dat' with linespoints title 'Insertion Sort'
