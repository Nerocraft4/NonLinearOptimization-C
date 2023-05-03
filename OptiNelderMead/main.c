#include "main.h"

int main() {
  clock_t  time_0, time_1;
	time_0=clock();

	int status;
  double time;
  status = NelderMead();
  //status = Derivada();

  printf("status: %s\n", gsl_strerror(status));

  time_1=clock();
  time = (double)(time_1-time_0)/CLOCKS_PER_SEC;
	printf("Execution Time: %f \n", time);
}
