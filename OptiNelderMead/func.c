#include "func.h"

// FUNCIO
double f(const gsl_vector* v, void* params) { //Rosenbrock basic function
  double x[12];
  double p = *(double*)params; 
  int n;

  for (n = 1; n < 11; n++){
      x[n]=gsl_vector_get(v, n-1);
  }
  x[0]=0;
  x[11]=0;

  double f_x = 0;

  for(n=1; n<11; n++){
    f_x += n*((1-p*cos(x[n])+sin(x[n-1]))-sin(x[n+1]));
  }
  return f_x;
}

// DERIVADA
void df (const gsl_vector* v, void* params, gsl_vector *df){
  double x[10];
  double p = *(double*)params; 
  int n;

  for(n=0; n<10; n++){
    x[n] = gsl_vector_get(v, n);
  }

  // LLenamos el gradiente
  gsl_vector_set(df, 0, p*sin(x[0])+2*cos(x[0]));
  for(n=0; n<9; n++){
    gsl_vector_set(df, n, (n+1)*p*sin(x[n])+2*cos(x[n]));
  }
  gsl_vector_set(df, 9, 10*p*sin(x[9])-9*cos(x[9]));

}

void fdf (const gsl_vector *x, void *params, double *F, gsl_vector *DF) {
	*F = f(x, params);
  df(x, params, DF);
}
