#include <stdio.h>
#include <stdlib.h>

typedef struct foo {
  int type;
} foo;

foo *new_foo(void *root, int type)
{
  void *nroot[1 + 2];
  nroot[0] = root;
  foo **var1 = (foo **)(nroot + 1);
  nroot[2] = NULL;
  root = nroot;

  *var1 = (foo *)malloc(sizeof(foo));
  (*var1)->type = type;

  printf("%p\n", root);
  printf("%p\n", var1);
  printf("%p\n", *var1);

  return *var1;
}

int main(int argc, char *argv[])
{
  void *root = NULL;

  foo *var1 = new_foo(root, 2);
  printf("%p\n", root);
  printf("v1=%p\n", var1);
  printf("%d\n", var1->type);

  return 0;
}
