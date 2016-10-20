#include "main.h"

void e() {
  printf("%p\n", NIL);
}

int main(int argc, char *argv[])
{
  printf("%p\n", NIL);
  e();
  d();
  d2();
  return 0;
}
