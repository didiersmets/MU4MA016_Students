set terminal png

set output "mesh1.png"
set title "Mesh 1"
show title
set xlabel "x"
show xlabel
set ylabel "y"
show ylabel
set key off
plot "mesh1.gnuplot" with lines
unset output

set output "mesh2.png"
set title "Mesh 2"
show title
set xlabel "x"
show xlabel
set ylabel "y"
show ylabel
set key off
plot "mesh2.gnuplot" with lines
unset output

set output "mesh3.png"
set title "Mesh 3"
show title
set hidden3d
splot "mesh3.gnuplot" with lines title "gridded", \
      "mesh3.gnuplot" with points nogrid pt 7 title "nogrid"
unset output

set output "mesh4.png"
set title "Mesh 4"
show title
set hidden3d
splot "mesh4.gnuplot" with lines title "gridded", \
      "mesh4.gnuplot" with points nogrid pt 7 title "nogrid"
unset output