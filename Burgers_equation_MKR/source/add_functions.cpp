
//--------------------------------------------
template<typename T2>
inline T2 series_create(T2 * SX,T2 t)  // сначала пишешь переменные шаблонного типа,а потом конкретного!!!
{
  T2 f1 = 0;
  T2 pow_f1 = 1;

  for (int i = 0 ;i <= ORDER_SER;i++)
   {
      f1 += SX[i]*pow_f1;
      pow_f1 *= t;
    }
      
return f1;

}
//-------------------------------------------
template<typename T2>
T2 eutken_transform( T2 * SX, T2 z)
{
    T2 f = 0;
    T2 det = (SX[1] - SX[2] * z);
    if ( abs(det) < 1e-20 )
                 f = series_create(SX,z);
    else
         f = ( pow ( SX[1] ,2 ) * z - SX[2] * SX[0] * z + SX[1] * SX[0] )/ det ;   
                     

    return f;
}
//-------------------------------------------
template<typename T2>
inline T2 app_pade_1_2(T2 * SX, T2 z)
{
    T2 f = 0;

    T2 a = -(SX[1] * SX[4] - SX[2] *SX[3])/(SX[1] *SX[3] - SX[2] * SX[2]);
    T2 b = (SX[2] * SX[4] - SX[3] *SX[3])/(SX[1] *SX[3] - SX[2] * SX[2]);

    T2 coeff_P_0 = SX[0];
    T2 coeff_P_1 = SX[1]+ a *SX[0];



    T2 coeff_Q_0 = 1;
    T2 coeff_Q_1 = a;
    T2 coeff_Q_2 = b;
   
    f = (coeff_P_0 + coeff_P_1 * z )/(coeff_Q_0 + coeff_Q_1 * z + coeff_Q_2 * z*z);                    

    return f;
}
//-------------------------------------------
template<typename T2>
inline T2 app_pade_2_1( T2 * SX, T2 z)
{
    T2 f = 0;

    T2 b1 = -  SX[3] /SX[2] ;

    T2 coeff_P_0 = SX[0];
    T2 coeff_P_1 = SX[1]+ b1 *SX[0];

    T2 coeff_P_2 = SX[2] +  b1  *SX[1]   ;

    T2 coeff_Q_0 = 1;
    T2 coeff_Q_1 = b1;

   
    f = (coeff_P_0 + coeff_P_1 * z + coeff_P_2 * z*z)/(coeff_Q_0 + coeff_Q_1 * z);                    

    return f;
}
//-------------------------------------------
template<typename T2>
inline T2 app_pade_3_1(T2 * SX, T2 z)
{
    T2 f = 0;

    T2 b1 = -  SX[4] /SX[3] ;

    T2 coeff_P_0 = SX[0];
    T2 coeff_P_1 = SX[1]+ b1 *SX[0];

    T2 coeff_P_2 = SX[2] +  b1  *SX[1]   ;
    T2 coeff_P_3 = SX[3] +  b1 *SX[2]   ;

    T2 coeff_Q_0 = 1;
    T2 coeff_Q_1 = b1;

   
    f = (coeff_P_0 + coeff_P_1 * z + coeff_P_2 * z*z + coeff_P_3 * z*z*z)/(coeff_Q_0 + coeff_Q_1 * z);                    

    return f;
}
//-------------------------------------------
template<typename T2>
inline T2 app_pade_2_2( T2 * SX, T2 z)
{
    T2 f = 0;

    T2 a = -(SX[1] * SX[4] - SX[2] *SX[3])/(SX[1] *SX[3] - SX[2] * SX[2]);
    T2 b = (SX[2] * SX[4] - SX[3] *SX[3])/(SX[1] *SX[3] - SX[2] * SX[2]);

    T2 coeff_P_0 = SX[0];
    T2 coeff_P_1 = SX[1]+ a *SX[0];

    T2 coeff_P_2 = SX[2] +  a  *SX[1] + b *SX[0]  ;

    T2 coeff_Q_0 = 1;
    T2 coeff_Q_1 = a;
    T2 coeff_Q_2 = b;
   
    f = (coeff_P_0 + coeff_P_1 * z + coeff_P_2 * z*z)/(coeff_Q_0 + coeff_Q_1 * z + coeff_Q_2 * z*z);                    

    return f;
}
//--------------------------------------------
template<typename T2>
inline T2 app_pade_3_3( T2 * SX, T2 z)
{
    T2 f = 0;

    T2 det = SX[1] * SX[3] * SX[5] - SX[1] * SX[4] *SX[4] - SX[2]*SX[2]*SX[5] + 2 * SX[2] *SX[3] *SX[4] -pow(SX[3],3);

    T2 a = -(SX[1] * SX[3] * SX[6] - SX[1] * SX[4] * SX[5] - SX[2]*SX[2]*SX[6]+SX[2]*SX[3]*SX[5] + SX[2] *SX[4] *SX[4] - SX[3]*SX[3]*SX[4])/det;

    T2 b = (SX[1] *SX[4] *SX[6] - SX[1] *SX[5]*SX[5] - SX[2] *SX[3] *SX[6] + SX[2]*SX[4]*SX[5]+SX[3]*SX[3]*SX[5]- SX[3]*SX[4]*SX[4])/det ;

    T2 c = - ( SX[2]*SX[4]*SX[6]-SX[2]*pow(SX[5],2)-pow(SX[3],2)*SX[6]+2*SX[3]*SX[4]*SX[5]-pow(SX[4],3) ) / det;

    T2 coeff_P_0 = SX[0];
    T2 coeff_P_1 = SX[1]+ a *SX[0];

    T2 coeff_P_2 = SX[2] +  b *SX[0]  + a  *SX[1] ;
    T2 coeff_P_3 = SX[3] +  a *SX[2]  + b  *SX[1] + c *SX[0] ;

    T2 coeff_Q_0 = 1;
    T2 coeff_Q_1 = a;
    T2 coeff_Q_2 = b;
    T2 coeff_Q_3 = c;
   
    f = (coeff_P_0 + coeff_P_1 * z + coeff_P_2 * z*z + coeff_P_3 * z*z*z)/(coeff_Q_0 + coeff_Q_1 * z + coeff_Q_2 * z*z + coeff_Q_3 * z*z*z);                    

    return f;
}

//--------------------------------------------
template<class T2>
T2 find_max(T2 **  SX)
{
    T2 max = 0;
    for (size_t j = 0; j < col_space_point - 1; j ++)
            if (abs(max) < abs(SX[j][0]))
                    max = abs(SX[j][0]);
                    
    return max;
}
//--------------------------------------------
template<typename T2>
T2 find_min_rad(T2 ** SX,int n_t)
{
    T2 min =10;
    int numb_j = 0;
    for (size_t j = 1; j < col_space_point - 1; j ++)
            if ( abs(min) > abs(SX[j][n_t-1]/SX[j][n_t]) )
                   {
                      min = abs(SX[j][n_t-1]/SX[j][n_t]);
                      numb_j = j;
                    }
 //   cout <<numb_j << endl;
                    
    return min;
}
//----------------------------------------------

template<typename T1>
inline T1 sum_pr(T1 *  SX1,T1 *  SX2,int N)
{
T1 var1=0;
for (int i = 0; i <=N;i++)
  var1 += SX1[i]*SX2[N-i];

return var1;
}
//--------------------------------------------------

template<typename T2>
inline bool vector_clear_but_first(T2 *  SX)
{
 for (int i = 1; i < ORDER_SER+2;i++)
    SX[i] = 0;
return 1;
}

