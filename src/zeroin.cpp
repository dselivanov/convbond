#include "convbond.h"
double zeroin(double ax, double bx, double (*f)(double, convBondParam*),double tol, convBondParam *cbparam)  
{
  double a,b,c;				// Abscissae, descr. see above
  double fa;				// f(a)
  double fb;				// f(b)
  double fc;				// f(c)
  int iter = 0;
  a = ax;
  b = bx;
  fa = (*f)(a, cbparam);
  fb = (*f)(b, cbparam);
  c = a;
  fc = fa;

  for(;;)		// Main iteration loop	
  {
    ++iter;
    double prev_step = b-a;		// Distance from the last but one
    double tol_act;			// Actual tolerance		
    double p;      			// Interpolation step is calcu- 
    double q;      			// lated in the form p/q; divi- 
    double new_step;      		// Step at this iteration       
   
    if( fabs(fc) < fabs(fb) )
    {                         		// Swap data for b to be the 	
	    a = b;  b = c;  c = a;          // best approximation		
	    fa=fb;  fb=fc;  fc=fa;
    }
    tol_act = 2*EPSILON*fabs(b) + tol/2;
    new_step = (c-b)/2;

    if( fabs(new_step) <= tol_act || fb == (double)0 )
      return b;				// Acceptable approx. is found	
    if( fabs(prev_step) >= tol_act	
	    && fabs(fa) > fabs(fb) )	// and was in true direction,	
    {					
  	register double t1,cb,t2;
  	cb = c-b;
  	if( a==c )			
  	{				// points linear interpolation 	
  	  t1 = fb/fa;			// can only be applied		
  	  p = cb*t1;
  	  q = 1.0 - t1;
   	}
  	else
  	{
  	  q = fa/fc;  t1 = fb/fc;  t2 = fb/fa;
  	  p = t2 * ( cb*q*(q-t1) - (b-a)*(t1-1.0) );
  	  q = (q-1.0) * (t1-1.0) * (t2-1.0);
  	}
  	if( p>(double)0 )	
  	  q = -q;			// posite sign; make p positive	
  	else				// and assign possible minus to	
  	  p = -p;			// q				
  
  	if( p < (0.75*cb*q-fabs(tol_act*q)/2)	// If b+p/q falls in [b,c]
  	    && p < fabs(prev_step*q/2) )	// and isn't too large	
  	  new_step = p/q;			// it is accepted. If p/q is too large then the	bissection procedure can 	reduce [b,c] range to more	extent			
      }
      if( fabs(new_step) < tol_act )	// Adjust the step to be not less
  	{
  		if( new_step > (double)0 )	// than tolerance		
  		{
  			new_step = tol_act;
  		} else
  		{
  			new_step = -tol_act;
  		}
  	}
      a = b;  fa = fb;			// Save the previous approx.	
      b += new_step;  fb = (*f)(b, cbparam);	// Do step to a new approxim.	
      if( (fb > 0 && fc > 0) || (fb < 0 && fc < 0) )
      {                 			// Adjust c for it to have a sign opposite to that of b  
        c = a;  fc = fa;
      }
      if(iter>MAXITER)
  	{
  		printf("iteration limit!\n");
  		return a;
  	}
  //printf("iteration %d, value %f \n", iter, a);
  }
}