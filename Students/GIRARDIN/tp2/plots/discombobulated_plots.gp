set terminal png size 1280,960

set output "discombocube.png"
set title "DISCOMBOCUBE!!!" font "Arial,16"
show title
set key off
set hidden3d
splot "cubidoo.gnuplot" with lines title "gridded", \
      "cubidoo.gnuplot" with points nogrid pt 7 title "nogrid"
unset output

set output "sphereidoo.png"
set title "DISCOMBOSPHERE!!!" font "Arial,16"
show title
set key off
set hidden3d
splot "sphere.gnuplot" with lines , \
      "sphere.gnuplot" with points nogrid pt 1 
unset output