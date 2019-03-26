//-------------------------------------------------
#include "include_files.h"
//----------------------------------------------

//добро пожаловать в программу Burgers_equation 1.5 //
//Автор А.А. Полуновский . Почта apap2009@yandex.ru //

//------------------------------------------------
//управляющие параметры//


#define steps 440 // количество шагов (по времени)
#define Rad (double)0.005 // длина шага (по времени)



#define step_space (double)0.01 // шаг по пространству



//на сколько точек делим каждый шаг
const size_t delta =10 ;

// количество гармоник ряда Фурье начального условия (!)
const size_t ORDER_GARMONIC = 200;

//порядок Тейлоровского многочлена по времени
const size_t ORDER_SER =10;

//значение вязкости
const double mu =0.001;

//выбор начального условия
const int initcond = 1;
 //1 - волна сильного разряжения
 //2 - волна слабого разряжения
 //3 - синус

 // амплитуда заданной начальной волны
const double A =1.0;


//-------------------------
// параметры для создания графиков/анимации//


// количество графиков гармоник, построенных в файле X.eps
const int number_graph = 10;

// номер кадра в анимации, который хотим построить в отдельном файле graph_moment.gif (число должно быть не больше, чем col_frame!)
const int  frame_graph = 6;


//--------------------------------------------------
//---------------------------------------------------