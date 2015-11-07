#include <stdio.h>
#include <stdlib.h>
#include "fuga.h"

void test()
{
  puts("test!");
}


I* newI() {
  return malloc(sizeof(I));
}
