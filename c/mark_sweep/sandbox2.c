#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int value;
} foo;

typedef struct{
  char value;
} var;

int main(int argc, char *argv[])
{
  void* v = malloc(1000);
  var* kk = (var*)v;
  kk->value = 1;
  printf("%d", kk->value);
  return 0;
}
