set terminal png size 800,600
set output 'sorting_comparison.png'
set logscale xy
set xlabel 'Array Size (N)'
set ylabel 'Execution Time (ms)'
set title 'Sorting Algorithm Performance Comparison'
set grid
set key left top
plot 'bubble_sort_data.txt' using 1:2 with linespoints title 'Bubble Sort', \
     'insertion_sort_data.txt' using 1:2 with linespoints title 'Insertion Sort', \
     'merge_sort_data.txt' using 1:2 with linespoints title 'Merge Sort'
