#include "main.h"
#include <stdlib.h>
#include "goldenSection.h"

int main(int argc, char* argv[]) {
  int status;
  printf("Introdueix un nombre entre 0 i 4: ");
  double x_min;
  scanf("%lf",&x_min);
  status = goldenSection(x_min);
  printf("status: %s\n", gsl_strerror(status));
}

