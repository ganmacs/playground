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

int comp_func2 (const void *c1, const void *c2)
{
  char* i1 = *(char **)c1;
  char* i2 = *(char **)c2;
  return strcmp(i1, i2);
}

int main(int argc, char *argv[])
{
  char* a[N] = {"deposit", "topic", "posited", "asdf", "delight"};
  char* b[N];

  for (int i = 0; i < N; i++) {
    b[i] = malloc(sizeof(a[i]));
    strcpy(b[i], a[i]);
  }


  for (int i = 0; i < N; i++) {
    qsort(b[i], strlen(b[i]), sizeof(char), comp_func);
  }

  qsort(b, N, sizeof(char*), comp_func2);

  for (int i = 0; i < N; i++) {
    printf("%s\n", b[i]);
  }

  for (int i = 0; i < N; i++) {
    free(b[i]);
  }

  return 0;
}
