#include <stdio.h>
#include <stdlib.h>

void error(char *msg)
{
  perror(msg);
  exit(1);
}
