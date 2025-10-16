set terminal pdf font "Times,11" size 5in, 3in
set output "plot.pdf"
plot "data_fct.txt" with lines
unset output
