#include "NelderMead.h"

int NelderMead() {
  // Function and derivative:  
  gsl_multimin_function F;
  F.n = 10; //dimension (number of variables) 
  F.f = &f; //function to optimize
  double p = 1.3;
  F.params = &p; //parameters of the function to optimitze

  // Set starting point:
  gsl_vector* x;
  x = gsl_vector_alloc(F.n);

  gsl_vector *ss;
	ss = gsl_vector_alloc(F.n);  

  // Set initial step sizes (only Nelder-Mead; construction of initial simplex):
  int i;
  for (i = 0; i< F.n; i++){
    gsl_vector_set(x, i, 0.1);
    gsl_vector_set(ss, i ,1);
  }

  //initialize minimizer:
  const gsl_multimin_fminimizer_type* T;
  T = gsl_multimin_fminimizer_nmsimplex;
  gsl_multimin_fminimizer* s = NULL;
  s = gsl_multimin_fminimizer_alloc(T, F.n);
  gsl_multimin_fminimizer_set(s, &F, x, ss);
  
  // Iterations control:
  int status;
  int iter = 0;
  int max_iter = 1000;
  double size;
  double tol = 0.001;
  printf("using %s method\n", gsl_multimin_fminimizer_name(s));
  
  do {
    iter++;
    status = gsl_multimin_fminimizer_iterate(s);

    if(status)
      break;

    size = gsl_multimin_fminimizer_size(s);
    status = gsl_multimin_test_size(size, tol);  //("tol" is the radius of simplex from centroid)
    if(status == GSL_SUCCESS)   // =0 (the simplex size is smaller than the tolerance)

    // PRINTS EN TERMINAL
    printf("Converged at iteration: %d\n", iter);
    printf("x = (");
    for (i=0; i<F.n; i++){
	    printf("%10.7f, ", gsl_vector_get(s->x, i));
    }
    printf(")");
    printf("Objective= %10.7lf\n",s->fval);

  } while(status == GSL_CONTINUE && iter < max_iter);  
  if(status == GSL_CONTINUE)  // =-2 (the simplex size is still bigger than the tolerance)
    printf("Maximum iterations reached.\n");

  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free(s);
  return status;
}

/*
### Definition of the types "gsl_multimin_function" and "gsl_multimin_function_fdf":
See manual GSL, chapter "Multidimensional Minimization".
The first for algorithms without derivatives.
The second for algorithms with derivatives, where we have to provide pointers
to both the function and the gradient.
*/

