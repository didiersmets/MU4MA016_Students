set terminal png
set output 'sorting_comparison.png'
set title 'Sorting Algorithm Performance Comparison'
set xlabel 'Array Size (N)'
set ylabel 'Time (seconds)'
set logscale xy
set grid
plot 'sorting_times.dat' using 1:2 title 'Bubble Sort' with linespoints,\
     'sorting_times.dat' using 1:3 title 'Insertion Sort' with linespoints,\
     'sorting_times.dat' using 1:4 title 'Merge Sort' with linespoints
