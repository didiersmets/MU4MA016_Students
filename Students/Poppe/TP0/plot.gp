set terminal pngcairo size 800,600
set output 'plot.png'

set title "Plot of f(x)=-sin(x)/x"
set xlabel "x"
set ylabel "y"
plot "data.txt" with lines title "-sin(x)/x"