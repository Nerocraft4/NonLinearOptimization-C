#include "main.h"

int main(int argc, char** argv) {
  int status;
  double startPoint;
  printf("Introdueix un punt inicial: ");
  scanf("%lf",&startPoint);
  status = newton(startPoint);
  printf("status: %d\n", status);
}
