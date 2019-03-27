#include "include_files.h"
#include "parameters.h"
#include "solver_file.h"
#include "source_funct.cuh"

#include "add_functions.h"

int main_solver(std::fstream &file1,std::fstream &file2,std::fstream &outvar1) {
	
	        scalar T = col_steps * ht;
	        std::cout << " Длина отрезка интегрирования по времени = " << col_steps * ht << std::endl;
	 
	        clock_t time2, time1 = clock();
	
	        int deviceCount;

            //Сколько устройств CUDA установлено на PC.
            cudaGetDeviceCount(&deviceCount);
            
            printf("Device count: %d\n\n", deviceCount);
	       
	       // приходится все таки на устройстве работать на чистом Си
	        scalar *dev_x0, *dev_x1; 
	       
	        scalar *x1 ,*x0;
	        	        
	        // размер массива из N чисел
	        ssize_t size = N * sizeof(scalar);
	        
	       // выделяем память на видюхе
	        cudaMalloc( (void**)&dev_x0, size );
	        cudaMalloc( (void**)&dev_x1, size );

	       
	        // выделяем память в оперативке 	        
	        x0 = (scalar*) malloc( size );
	        x1 = (scalar*) malloc( size );
	        
	       //задаем н. у.
	        for (ssize_t l=1 ; l < N-1; ++l)
                 x0[l] =  ( l < (int)(N - 1)/2) ? 1 : 0;

            // задаем г. у.
            x0[0] = 1;
            x0[N-1] = 0;
            
           // задаем размерности сетки на видеокарте
	       dim3 threads ( BLOCK_SIZE );
           dim3 blocks  ( N / threads.x);
           
           bool flag = 0;
           scalar my_x = 0;
            	       
           // запускаем цикл по времени  
         //---------------------------------------------------------
         for (int k=1 ;k <= col_steps; k++)
        {
		   time2 = clock();
		   
		     // create cuda event handles
            cudaEvent_t start, stop;
            float gpuTime = 0.0f;
            cudaEventCreate ( &start );
            cudaEventCreate ( &stop );
            
             // asynchronously issue work to the GPU (all to stream 0)
            cudaEventRecord ( start, 0 );
		   
	       // копируем содержимое переменных из оперативы в переменные на девайсе      
	       cudaMemcpy(dev_x0 , x0, size, cudaMemcpyHostToDevice );
	        	        
	       ode_euler<<< blocks , threads >>>(dev_x0, dev_x1, mu, hx, a, b, (int)N, ht);
	        
	        // Обратно копируем       
	       cudaMemcpy(x1, dev_x1 ,size, cudaMemcpyDeviceToHost );
	       
	       //определяем точку завершения работы видеокарты
	       cudaEventRecord ( stop, 0 );
           cudaEventSynchronize ( stop );
           cudaEventElapsedTime ( &gpuTime, start, stop );
	       
	       
	       for (ssize_t i=0 ; i < N; ++i)
	       {
                 x0[i] = x1[i] ;
	           if (x0[i] > 1e+8)
                     flag = 1;
	       }
	        
	        
	        if ( k % (int) (col_steps / col_frame)  == 0)
               {
                  my_x = 0;
                  
                  file1 << k*ht<<" ";
                  for (int j=0 ; j < N; ++j)
                  { 
                     file1 <<  x1[j] << " " ;
                     file2 <<  my_x << " " << x1[j] << std::endl;
                     my_x += hx;
                  }
                  
                  file1 << std::endl;
                  file2 << std::endl;   
                  file2 << std::endl;
                }   
	        
	        
	        
	         if (flag == 1) 
             {
                std::cout << "приближенное решение уходит в бесконечность " << std::endl;
                break;
             }
             
              time1 = clock() - time1;
              time2 = clock() - time2;
             
             if (k % 100 == 0)
            { 
			  printf("time spent executing by the GPU: %.2f millseconds\n", gpuTime );
		      std::cout << k <<"-ый шаг интегрирования" << std::endl;
              std::cout <<"значение " << (int)N/2 <<"-ой расчетной точки: "<< x1[(int)N/2] << " в " << k*ht <<"-ую секунду" << std::endl;
              std::cout << "проинтегрирован отрезок = " << k*ht << std::endl;
              std::cout << "выполнено :" << k*ht*100/T <<"%" << std::endl;
              std::cout << "максимальное значение функции в данный t : " << find_max(x1) << std::endl;


              std::cout << "время, потраченное на одну итерацию :" << ((double) time2)/CLOCKS_PER_SEC << " секунд(ы)" << std::endl;
              std::cout << "общее прошедшее время : " << ((double) time1)/CLOCKS_PER_SEC << " секунд(ы)" << std::endl;
    
              std::cout << "----------------------------" << std::endl;
              std::cout << std::endl;
            }
	        
	        
	     }
	     //---------------------------------------------------------------------
	     
	        
	        // освобождаем память
	        free( x0 ); free( x1 ); 
	        cudaFree( dev_x0 );
	        cudaFree( dev_x1 );
	        
	        
	        
	        //передаем необходимые переменные в gnuplot

            outvar1 << "col_frame1 = " <<  col_frame << std::endl ;
            outvar1 << "T1 = " <<  T << std::endl ;
            outvar1 << "NUMBER_GR = " <<  10<< std::endl;//col_space_point << endl ;
            outvar1 << "frame_cadr = " << 2 << std::endl;
            outvar1 << "wall_left_gr = " << 0 << std::endl;
            outvar1 << "wall_right_gr = " << L - hx << std::endl;
	                   
            return 0;
}
