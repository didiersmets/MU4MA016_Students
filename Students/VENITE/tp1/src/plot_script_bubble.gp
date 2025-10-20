set terminal pngcairo size 800,600
set output 'bubble_sort_performance.png'
set title 'Bubble Sort Performance'
set xlabel 'Number of elements (N)'
set ylabel 'Execution time (seconds)'
set logscale xy
set grid
plot 'bubble_times.dat' with linespoints title 'Bubble Sort'
