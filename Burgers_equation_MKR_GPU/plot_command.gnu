#!/usr/bin/gnuplot

set term eps
set output "X.eps"
set grid xtics ytics
set bar 0
set xzeroaxis lt -1
set yzeroaxis lt -1

load "vars.txt"
set xrange [0:T1]

do for [i=3:NUMBER_GR] {
plot "output_data_point_funct_2.txt" using 1:i linewidth 1  with lines  title sprintf("%g point",i-2)
}

#------------------------------------------------------------------------
set term gif animate optimize delay 2 size 1000, 1000 #background "ffeedf" crop 
# основные настройки gif файла, delay -задержка между кадрами
set xrange [wall_left_gr:wall_right_gr]
set yrange [-3:3]
set key off # отключаем легенду на графике
unset colorbox # отключение вывода палитры
set grid xtics
set size square
set bar 0
set output "animate.gif"
set xzeroaxis lt -1


do for [i=0:col_frame1-1] {
  plot "output_data_animate_2.txt"  index i using 1:2 linewidth 2 with lines  
}
 
set output "graph_moment.gif"

plot "output_data_animate_2.txt"  index frame_cadr using 1:2 linewidth 2 with lines 


