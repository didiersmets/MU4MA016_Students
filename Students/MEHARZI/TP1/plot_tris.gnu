set terminal pngcairo size 800,600
set output "tris.png"

set title "Comparaison des tris"
set xlabel "N"
set ylabel "Temps (s)"
set logscale xy
set grid

plot "bubble_times.dat"    using 1:2 with linespoints title "Bubble sort", \
     "insertion_times.dat" using 1:2 with linespoints title "Insertion sort", \
     "merge_times.dat"     using 1:2 with linespoints title "Merge sort"
