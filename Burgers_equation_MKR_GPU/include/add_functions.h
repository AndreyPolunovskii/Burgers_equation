

template<class T2>
T2 find_max(T2 * SX)
{
    T2 max = 0;
    for (size_t j = 0; j < N - 1; j ++)
            if (abs(max) < abs(SX[j]))
                    max = abs(SX[j]);
                    
    return max;
}
//--------------------------------------------
scalar inifunct(size_t &la)
{

  switch (initcond)
   {
    // 2*A*(-cos(pi*la/4)+cos(3*pi*la/4))/(pi*la)
    case 1 : return (scalar) ( sin( 2* Pi*((int)la)/(int)(N - 1) ) );

    case 2 : return  2;

    case 3 : return  ((int)la == 1) ? 3 : 0 ;
   }
   
   return 0;
}
//---------------------------------------------


