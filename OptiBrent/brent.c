#include "brent.h"

int brent(double x_min) {
  gsl_function F;
  F.function = &f;
  F.params = NULL;

  //double x_min =  3;        /* initial guess */
  double x_lower = 0, x_upper = 4; /* initial interval */
  // (exercise) make initial guess an input of the user, collected in
  // function main() and passed as argument to function goldenSection()
  
  double f_min;

  const gsl_min_fminimizer_type* T;
  T = gsl_min_fminimizer_brent;
  gsl_min_fminimizer* s;
  s = gsl_min_fminimizer_alloc(T);
  gsl_min_fminimizer_set(s, &F, x_min, x_lower, x_upper);

  int status;
  int iter = 0;
  int max_iter = 100;
  double epsabs = 0.001;
  double epsrel = 0;

  printf("using %s method\n", gsl_min_fminimizer_name(s));
  printf("%5s [%10s, %10s] %10s       f_min %10s\n", "iter", "lower", "upper", "min", "err(est.)");
  printf("%5d [%.8f, %.8f] %.8f %.8f %.8f\n", iter, x_lower, x_upper, x_min, F.function(x_min,F.params), x_upper - x_lower);

  do {
    iter++;
    status = gsl_min_fminimizer_iterate(s);
    x_min = gsl_min_fminimizer_x_minimum(s);
    x_lower = gsl_min_fminimizer_x_lower(s);
    x_upper = gsl_min_fminimizer_x_upper(s);
    f_min = gsl_min_fminimizer_f_minimum(s);

    status = gsl_min_test_interval(x_lower, x_upper, epsabs, epsrel);
    if(status == GSL_SUCCESS)
      printf("Converged:\n");

    printf("%5d [%.8f, %.8f] "
           "%.8f %.8f %.8f\n",
           iter, x_lower, x_upper, x_min, f_min, x_upper - x_lower);
    // (exercise) add the value of the function at every iteration to previous printf
    // in the best point as well as in the endpoints of the interval, using
    // function gsl_min_fminimizer_f_minimum, etc (see the manual).

  } while(status == GSL_CONTINUE && iter < max_iter);

  gsl_min_fminimizer_free(s);
  return status;
}

// (exercise) Write another program to use the Brent minimizer (see the manual)

/*
### Definition of the type "gsl_function":

struct gsl_function_struct
{
    double (* function) (double x, void * params);
    void * params;
};

typedef struct gsl_function_struct gsl_function ;

*/
