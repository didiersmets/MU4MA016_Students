#Courbe bubble
set logscale x
set logscale y
set title "Bubble"

plot "N_versus_execution_time.dat" using 1:2 title "Bubble"

#Courbe insertion
set logscale x
set logscale y
set title "Insertion"

plot "N_versus_execution_time.dat" using 1:3 title "Insertion"

#Courbe merge
set logscale x
set logscale y 
set title "Merge"

plot "N_versus_execution_time.dat" using 1:4 title "Merge"

pause -1 "Hit return"
exit

