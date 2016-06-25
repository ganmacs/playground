#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int comp_func (const void *c1, const void *c2)
{
  char i1 = *(char *)c1;
  char i2 = *(char *)c2;

  return i1 - i2;
}

int main(int argc, char *argv[])
{
  char* a[] = {"deposit", "topic", "posited", "asdf", "delight"};
  char* b[N];

  for (int i = 0; i < N; i++) {
    b[i] = malloc(sizeof(a[i]));
  }

  for (int i = 0; i < N; i++) {
    b[i] = a[i];
    printf("%s\n", b[i]);
    qsort(b[i], sizeof(b[i])/sizeof(char) - 1, sizeof(char), comp_func);
    printf("%s\n", b[i]);
  }

  return 0;
}
