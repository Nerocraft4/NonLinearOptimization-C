#include "main.h"
#include <stdlib.h>
#include "brent.h"

int main(int argc, char* argv[]) {
  int status;
  double x_min;
  printf("Introdueix un nombre real entre 0 i 4: ");
  scanf("%lf",&x_min);
  status = brent(x_min);
  printf("status: %s\n", gsl_strerror(status));
}
