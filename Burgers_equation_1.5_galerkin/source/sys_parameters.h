#include "include_files.h"
#include "PARAMETERS.h"


#define wall_space (double)2*pi // правая граница расчетного пространства, еще на омегу влияет

// системная переменная
const int col_garmonic_init = (ORDER_SER+1)*(ORDER_GARMONIC+2);


// приближенное значение длины отрезка интегрирования по времени
const double T = steps*Rad ;

//c этой омегой не все ясно,но считает вроде правильно
const double omega =2*pi/(2*wall_space);


const size_t col_point = delta*steps -1; // количество точек по времени



//количество кадров для анимации( желательно чтобы это число было кратно числу col_point) и не больше чем col_point!!
const double col_frame = col_point *2 / steps;
// чем меньше кадров (col_frame), тем быстрее показывает
// так же чем меньше col_point , тем медленнее показывает
