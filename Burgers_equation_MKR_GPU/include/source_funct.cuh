

__device__ inline void fRight(scalar * x0,scalar * x1,scalar mu,scalar hx,scalar a,scalar b,int N1)
{
	const int ix = blockDim.x * blockIdx.x + threadIdx.x;
	
	if ( ix == 0 )
	        x1[ ix ] = a;
	        
    if ( ix == N1 - 1 )
	        x1[ ix ] = b; 
	
	if ( ix != 0 && ix != N1-1 )         
     x1[ix] = (x0[ix - 1] * x0[ix - 1] -   x0[ ix ] * x0[ ix ])/hx + mu * ( x0[ ix - 1 ] - 2 * x0[ix]  + x0[ ix + 1 ] )/(hx*hx); 
	
	       
	
}
//---------------------------

__global__ void ode_euler(scalar * x0,scalar * x1,scalar mu,scalar hx,scalar a,scalar b,int N1,scalar ht)
{
	const int ix = blockDim.x * blockIdx.x + threadIdx.x;
	
	fRight(x0,x1,mu,hx,a,b,N1);
	
	
	if ( ix != 0 && ix != N1-1 )
	    x1[ix] = x1[ix]*ht + x0[ix];
	
}
//---------------------------
