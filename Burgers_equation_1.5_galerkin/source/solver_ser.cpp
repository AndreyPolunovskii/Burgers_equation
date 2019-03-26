#include "solve_ser.h"



//----------------------------------------------
inline double inifunct(size_t &la)
{

  switch (initcond)
   {
    // 2*A*(-cos(pi*la/4)+cos(3*pi*la/4))/(pi*la)
    case 1 : return  -2*A*(-1+cos(3*pi*la/4))/(pi*la);

    case 2 : return  -2*A*(-cos(pi*la/2)+cos(pi*la))/(pi*la);

    case 3 : return  ((int)la == 1) ? A : 0 ;
   }
}
//---------------------------------------------------------------------------
//вроде отладили эти реккурентные формулы произведения рядов Фурье!!
template<typename T1>
inline T1 sum_pr(vector< vector<T1> > &matrix,size_t &j1,size_t &n1)
{

T1 sum1=0;

 for (int m = 1; m <= (int) ORDER_GARMONIC*(n1+2);m++)
 //for (int m = 1; m <= (int) ORDER_GARMONIC;m++)
     for (int k=0; k<= (int) n1 ;k++)
     {
      if (m+ (int)j1 <= ORDER_GARMONIC*(n1+2))
 //     if (m+ (int)j1 <= ORDER_GARMONIC)
        sum1 += matrix[m][k]*(abs(m-(int)j1)*omega*matrix[abs(m-(int)j1)][(int)n1-k]-(m+(int)j1)*omega*matrix[m+(int)j1][(int)n1-k]);
        else
          sum1 += matrix[m][k]*(abs(m-(int)j1)*omega*matrix[abs(m-(int)j1)][(int)n1-k]);
     }


return sum1;
}
//надо бы еще поотлаживать эти формулы
//-------------------------------------------------

template<typename T2>
inline T2 series_create1(vector<T2> &SX,T2 t,int N)  // сначала пишешь переменные шаблонного типа,а потом конкретного!!!
{
  T2 f1 = 0;

  for (int i = 0 ;i < N;i++)
      f1 += SX[i]*pow(t,i);



return f1;

}

//--------------------------------------------------
inline double U_err(vector< double > & vector_coeff,double x)
{
  double funct = 0;

for (int j=0;j <= vector_coeff.size(); ++j)
      funct += vector_coeff[j]*sin(omega*j*x);

return funct;

}
//--------------------------------------------------
bool solver_ser1(std::fstream &file1,std::fstream &file2,std::fstream &outvar1)
{

int t,t1;
vector< vector<double> > matrix1(col_garmonic_init+1);
vector< vector<double> > matrix2(ORDER_GARMONIC+1);
vector< double > T_zn,Zn_garm;
double t1_f=0;

//для вычисления ошибки вычислений
vector< double > vect_coeff1(col_garmonic_init+1);
vector< double > vect_err1;



double global_err = 0;
double local_err = 0;
double avarage_maxgarm_err = 0;


t = time(NULL);
t1 = time(NULL);
//инициализируем массивы
     #pragma omp parallel for
     for (size_t j=0 ; j <= col_garmonic_init; ++j)
     {
                   matrix1[j].resize(ORDER_SER+3);
      }


// обнуляем нулевую гармонику
      #pragma omp parallel for
      for (size_t i=0 ; i < ORDER_SER+3; ++i)
      {
      matrix1[0][i] = 0;
      }

     #pragma omp parallel for
     for (size_t j=0 ; j <= ORDER_GARMONIC; ++j)
     {
                   matrix2[j].resize(col_point+1);
      }

//задаем начальные условия


     #pragma omp parallel for
     for (size_t l=1 ; l <= ORDER_GARMONIC; ++l)
     {
                   matrix1[l][0] = inifunct(l);
      }

      #pragma omp parallel for
       for (size_t l=ORDER_GARMONIC+1 ; l <= col_garmonic_init; ++l)
     {
                   matrix1[l][0] = 0 ;
      }

     #pragma omp parallel for
     for (size_t l=1 ; l <=ORDER_GARMONIC; ++l)
     {
                    matrix2[l][0] = inifunct(l) ;
      }


//--------------------------------------------
// пошел основной цикл
//--------------------------------------------
for (int k=1 ;k <=steps; k++)
  {

      for (size_t n=0; n<ORDER_SER; ++n)
        {
       #pragma omp parallel for firstprivate(n,mu,omega)
          for (size_t j=0 ; j <= ORDER_GARMONIC*(n+2); ++j)
    //      for (size_t j=0 ; j <= ORDER_GARMONIC; ++j)
          {
                   matrix1[j][n+1] = -(sum_pr(matrix1,j,n)/2+mu*pow((double)j*omega,2)*matrix1[j][n])/(n+1);
                // сами реккурентные формулы, по которым считаем коэффициенты ряда
       //     if (k==3)    cout <<  matrix1[j][n+1] <<" " <<j << " " << n+1 << endl;
          }
        }

     for (int i = delta*(k-1); i <= delta*k;i++)
        {
            t1_f = (i - delta*(k-1))*Rad/delta;

            for (int j=0 ; j <= ORDER_GARMONIC; ++j)
              matrix2[j][i]= series_create1(matrix1[j],t1_f,ORDER_SER);
            T_zn.push_back(i*Rad/delta);
        }
        // вычисляем конкретные значения функции , используя коэффициенты ряда




   //вычисляем ошибки расчета
   #pragma omp parallel for
   for (size_t j=0 ; j <= ORDER_GARMONIC; ++j)
   {
           vect_coeff1[j]  =  matrix1[j][ORDER_SER]*pow(Rad,(int)(ORDER_SER));
    }

   for (double x=0; x <=wall_space ; x+=step_space)
    {
          vect_err1.push_back(abs(U_err(vect_coeff1,x)));
    }

   local_err =  *max_element(vect_err1.begin(),vect_err1.end());
   global_err +=  local_err;

   avarage_maxgarm_err += abs(matrix2[ORDER_GARMONIC][delta*k]);

t1 = time(NULL) - t ;
       // вычисляем конкретные значения функции , используя коэффициенты ряда
cout << "проинтегрирован отрезок = " << k*Rad << endl;
cout << "выполнено :" << k*Rad*100/T <<"%" << endl;
cout << "(максимальная по пространству) локальная ошибка по времени : " << local_err  << endl;
cout << "значение высшей гармоники (норма по пространству) :" << abs(matrix2[ORDER_GARMONIC][delta*k]) << endl;
cout << "прошедшее время : " << t1 << " секунд(ы)" << endl;
cout << endl;

       //перезаписываем начальное условие (аналитическое продолжение)
 #pragma omp parallel for
   for (size_t j=0 ; j <= ORDER_GARMONIC; ++j)
   {
              matrix1[j].clear();
              matrix1[j][0]=series_create1(matrix1[j],Rad,ORDER_SER);

    }

 #pragma omp parallel for firstprivate(col_garmonic_init)
     for (size_t l=ORDER_GARMONIC+1 ; l <= col_garmonic_init; ++l)
     {
                   matrix1[l][0] = 0;
      }


  }
//-------------------------------------------
//закончился основной цикл


// выводим информацию в файл
// 1-cтолбец = моменты времени
// остальные столбцы - коэффициенты гармоник в порядке возрастания

file1.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
file1.precision(15);//15- количество знаков после запятой,для double 15 - это вроде максимум


T_zn[0] = 0.000;
//--------------------------------------------
 for (int i = 0 ; i <= (int)col_point ; ++i)
   {
     file1 << T_zn[i] <<" ";
     for (int j = 0 ; j <= ORDER_GARMONIC; ++j)
        {
         file1 <<  matrix2[j][i] << " " ;
        }
        file1 << endl;
   }

//-------------------------------------------

//выбираем отрезок зарисовки кривой в зависимости от начального условия
int n0=0;
double startborder =0;
if (initcond == 3) n0 = 2 ; else n0 = 1;
if (initcond == 1) startborder = wall_space/2; else  startborder =0;

//передаем необходимые переменные в gnuplot


outvar1 << "col_frame1 = " <<  col_frame - 11 << endl ;
outvar1 << "T1 = " <<  T_zn[col_point] << endl ;
outvar1 << "NUMBER_GR = " <<  number_graph << endl ;
outvar1 << "frame_cadr = " << frame_graph << endl;
outvar1 << "wall_left_gr = " << startborder << endl;
outvar1 << "wall_right_gr = " << n0*wall_space << endl;


//-------------------------------------------
char symb;

t = time(NULL) - t ;


cout << "расчет окончен. " <<  endl;
cout << "(максимальная по пространству) Общая ошибка по времени = " << global_err << endl;
cout << "Cреднее значение высшей гармоники = " << avarage_maxgarm_err/((double)steps) << endl;
cout << "время расчета : " << t << " секунд(ы)" << endl;

cout << " Cоздаю графики..." << endl;
//-------------------------------------------
//-----------------------------------------


//-----------------------------------------------
//вывод для анимации (приходится вручную в зависимости от параметра steps количество кадров анимации менять)
//-----------------------------------------------
file2.setf(ios_base::fixed,ios_base::floatfield);
file2.precision(15);



double funct = 0  ;
int i=0;

while (i < (int)col_point)
{
 for (double x=startborder; x <=n0*wall_space ; x+=step_space)
 {
    for (int j=0;j <= ORDER_GARMONIC; ++j)
      funct+=matrix2[j][i]* sin(omega*j*x);

    file2 <<  x << " " << funct << endl;
    funct = 0;
 }
    file2 << endl;
    file2 << endl;
    file2 << endl;
    i += (int) col_point / col_frame ;

}

//выводим необходимые переменные в gnuplot

return 0;
}
