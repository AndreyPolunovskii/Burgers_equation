#include "solver_file.h"
#include "add_functions.cpp"


//--------------------------------------------------
bool main_solver(scalar col_steps,std::fstream &file1,std::fstream &file2,std::fstream &outvar1)
{

scalar ** matrix_series = new scalar * [col_space_point];
scalar max_point;
scalar buf;
scalar Rad = RAD;
int flag = 0;
clock_t time2, time1 = clock();

scalar x = 0  ;
int k ;

file1.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
file1.precision(15);//15- количество знаков после запятой,для double 15 - это вроде максимум


file2.setf(ios_base::fixed,ios_base::floatfield);
file2.precision(15);

//инициализируем массивы

    
     #pragma omp parallel for
     for (size_t j=0 ; j < col_space_point; ++j)
                   matrix_series[j] = new scalar [ORDER_SER + 3] ;
 
    
      
//задаем начальные условия
     #pragma omp parallel for
     for (size_t l=1 ; l < col_space_point-1; ++l)
                 if ( l < (int)(col_space_point - 1)/2)
                   matrix_series[l][0] = 1;
                  else
                     matrix_series[l][0] = 0;
                      
     


// задаем граничные условия
      #pragma omp parallel for
      for (size_t i=0 ; i <= ORDER_SER; ++i)
      {
        matrix_series[0][i] = 1;
        matrix_series[col_space_point-1][i] = 0;
      }
     


//------------------------------------------------


for (k=1 ;k <=(int)(col_steps); k++)
  {

     time2 = clock();

    //      #pragma omp parallel for  
          for (int j=1; j<col_space_point-1; j++)
                 for (int n=0; n<=ORDER_SER; n++)
                       matrix_series[j][n+1] =  ( sum_pr(matrix_series[j-1], matrix_series[j-1],n)/h- sum_pr(matrix_series[j], matrix_series[j],n)/h  + mu*(matrix_series[j+1][n]-2*matrix_series[j][n]+matrix_series[j-1][n])/(h*h) )/((scalar)n+1.);
        

     //------------------------------------------
       //     #pragma omp parallel for 
            for (int j=0 ; j < col_space_point; ++j)
             {
               matrix_series[j][0]=series_create(matrix_series[j],RAD);
               if (matrix_series[j][0] > 1e+3)
                               flag = 1; 
               vector_clear_but_first(matrix_series[j]);
//eutken_transform(matrix_series[j],t1_f);//app_pade_2_2(matrix_series[j],t1_f);//series_create(matrix_series[j],t1_f,ORDER_SER);//// //eutken_transform(matrix_series[j],t1_f);   
      
             }


              if ( k % (int) (time_steps / col_frame)  == 0)
               {
                  x = 0;
                  file1 << k*Rad<<" ";
                  for (int j=0 ; j < col_space_point; ++j)
                  { 
                     file1 <<  matrix_series[j][0] << " " ;
                     file2 <<  x << " " << matrix_series[j][0] << endl;
                     x +=h;
                  }
                  file1 << endl;
                  file2 << endl;   
                  file2 << endl;
                }   
  
    
     

      if (flag == 1) 
       {
        cout << "приближенное решение уходит в бесконечность " << endl;
        break;
       }
   
    
    

  //  cout << "----------------------------" << endl;
       time1 = clock() - time1;
       time2 = clock() - time2;
 
     if (k % 100 == 0)
       { 
       cout <<"значение " << (int)col_space_point/2 <<"-ой расчетной точки: "<< matrix_series[(int)col_space_point/2][0] << " в " << k*Rad <<"-ую секунду" << endl;
       cout << "проинтегрирован отрезок = " << k*Rad << endl;
       cout << "выполнено :" << k*Rad*100/T <<"%" << endl;
       cout << "максимальное значение функции в данный t : " << find_max(matrix_series) << endl;


       cout << "время, потраченное на одну итерацию :" << ((double) time2)/CLOCKS_PER_SEC << " секунд(ы)" << endl;
       cout << "общее прошедшее время : " << ((double) time1)/CLOCKS_PER_SEC << " секунд(ы)" << endl;
    
       cout << "----------------------------" << endl;
       cout << endl;
      }


    
 
  }


 

//----------------------------------------
//----------------------------------------

    max_point = find_max(matrix_series);
    cout << "максимальное значение распр. функции в послед. момент времени = " << max_point <<endl;



//передаем необходимые переменные в gnuplot

outvar1 << "col_frame1 = " <<  col_frame << endl ;
outvar1 << "T1 = " <<  k * RAD << endl ;
outvar1 << "NUMBER_GR = " <<  10<< endl;//col_space_point << endl ;
outvar1 << "frame_cadr = " << 2 << endl;
outvar1 << "wall_left_gr = " << 0 << endl;
outvar1 << "wall_right_gr = " << L - h << endl;


return 0;
}
