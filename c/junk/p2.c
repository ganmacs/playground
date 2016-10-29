#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct obj_t {
  char *name;
  int value;
  void  *next;
} obj_t;


int main(int argc, char *argv[])
{

  char *new = malloc(1);
  memcpy(new, "abc", 2);
  printf("%s\n", new);

  return 0;
}
