
//количество использованных знаков 
const int col_sign =20;

// порядок многочлена по времени
#define ORDER_SER 2



//410
// радиус сходимости ( примерный ) для рядов по t 
#define RAD  2e-5




// количество аналитических продолжений по времени
const int time_steps =(int) ( 1 /(double)RAD);///(int) ( 1 /(double)RAD);



//количество точек по пространству
#define col_space_point (int)250

// длина отрезка по пространству
const scalar L = 1.; 

// шаг по пространству
const scalar h = (L/(double)col_space_point); 

const scalar mu = 0.;//вязкость

//длина отрезка по времени
const scalar T =  time_steps  * RAD;

// количество кадров в анимации  и в точек в графиках
const scalar col_frame = 200;






