set xlabel "timp"
set ylabel "dimensiune date"
plot 'plot.txt' using 1:2 with linespoints title 'Mergesort', '' using 1:3 with linespoints title 'Countsort', '' using 1:4 with linespoints title 'Radixsort'