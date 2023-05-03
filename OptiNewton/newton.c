#include "newton.h"
#include <math.h>

int newton(double startPoint) {
  struct Function {
    double (*f)(double x, void* params);
    double (*df)(double x, void* params);
    double (*ddf)(double x, void* params);
    void* params;
  };
  struct Function F;
  F.f = &f;
  F.df = &df;
  F.ddf = &ddf;
  F.params = NULL;

  double x_min_anterior = 0;
  double differ = 1000;
  double differy= 1000;
  double x_min = startPoint; /* initial guess */
  double f_min = F.f(x_min, F.params);
  double f_min_anterior = 0;
  // double x_lower = 0.0, x_upper = 6.0; /* initial interval, unused */
  // (exercise) make initial guess an input of the user, collected in
  // function main() and passed as argument to function newton()
  double TOL = 0.000000000001;
  int flag = 0;
  int status = 0;
  int iter = 0;
  int max_iter = 10;
  // double epsabs = 0.001;  /* unsued */
  // double epsrel = 0; /* unsued */

  printf("using Newton method...\n");
  printf("%5s | %11s        | %12s       |  %12s     |   %12s       \n", "iter", "min","f(min)", "|diff_x|","|diff_f(x)|");
  printf("------|--------------------|--------------------|-------------------|-------------------\n");
  if(x_min<0){
    printf("%5d | %.15f |        undef       |       undef       |       undef\n", iter, x_min);
  }else{
    printf("%5d | +%.15f |        undef       |       undef       |       undef\n", iter, x_min);
  }


  do {
    iter++;
    x_min_anterior = x_min;
    x_min = x_min - F.df(x_min, F.params) / F.ddf(x_min, F.params);  // could be extracted to a function Newton_iteration();
    differ = x_min-x_min_anterior;
    f_min_anterior = f_min;
    f_min = F.f(x_min, F.params);
    differy=f_min-f_min_anterior;
    if (fabs(differ)<TOL){
      flag = 1;
    }
    if (fabs(differy)<TOL){
      flag = 1;
    }
    // (exercise) compare consecutives values of x_min and raise a flag if difference is < 10^(-12)
    // and in that case print "Converged" and finish the iterations
    // (exercise) compare consecutive function values and raise a flag if difference is < 10^(-12),
    // and in that case also print "Converged" and finish the iterations
    if (flag == 1){
      printf("Converged! Result:\n");
    }
    // if(difference small)
    // printf("Converged:\n");
    //
    if (F.ddf(x_min, F.params)<0){
      flag = 1;
      printf("Negative second derivative\n");
      status = 1;
    }
    // (exercise) If the second derivative is negative, stop the iterations,
    // print an informative message and change status to 1
    if(x_min<0){
      if(f_min<0){
        printf("%5d | %.15f | %.15f | %.15f | %.15f\n", iter, x_min, f_min, fabs(differ), fabs(differy));
      }else{
        printf("%5d | %.15f | +%.15f | %.15f | %.15f\n", iter, x_min, f_min, fabs(differ), fabs(differy));
      }
    }else{
      if(f_min<0){
        printf("%5d | +%.15f | %.15f | %.15f | %.15f\n", iter, x_min, f_min, fabs(differ), fabs(differy));
      }else{
        printf("%5d | +%.15f | +%.15f | %.15f | %.15f\n", iter, x_min, f_min, fabs(differ), fabs(differy));
      }
    }
    // (exercise) add the value of the function at every iteration to this printf

  } while(iter < max_iter && flag==0);

  if( iter >= max_iter){
    printf("Max iterations reached (%d), convergence not reached\n",iter);
    status=2;
  }
  // (exercise) if maximum iterations are reached, print an informative message
  // and change status to 2

  return status;
}
