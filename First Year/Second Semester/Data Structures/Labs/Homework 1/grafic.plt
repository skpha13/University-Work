set datafile missing "-"
set xlabel "Dimensiune date"
set ylabel "Timp"
plot 'plot2.txt' using 1:2 with linespoints title 'Mergesort', '' using 1:3 with linespoints title 'Countsort', '' using 1:4 with linespoints title 'Interschimbare', '' using 1:5 with linespoints title 'Shellsort', '' using 1:6 with linespoints title 'Radix10', '' using 1:11 with linespoints title 'Radix2^16', '' using 1:12 with linespoints title 'Nativ'