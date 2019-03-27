#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED

typedef double scalar;

namespace parameters_solver {

#define Pi (scalar) 3.1415926535897932384626433832795028841971

#define N 1000 // количество точек

#define BLOCK_SIZE 20 // размерность блока


scalar a = 1;
scalar b = 0;

// шаг по пространству
scalar hx = 0.001;

scalar L = hx * N;

// шаг по времени
scalar ht = 0.00001;

int col_steps = 6000; // количество шагов по времени

scalar mu = 0.001;

//тип граничных условий
const int initcond = 1;

// количество кадров в анимации  и в точек в графиках
const int col_frame = (int) col_steps/30;

}

using namespace parameters_solver;

#endif // PARAMETERS_H_INCLUDED
