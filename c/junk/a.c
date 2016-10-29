#include <stdio.h>
#include <stdlib.h>

typedef struct atype{
  int a;
  void *b;
} atype;

atype *foo()
{
  atype a = { 0 };

  printf("%d\n", a.a);
  printf("%p\n", a.b);

  atype *v = malloc(sizeof(atype));
  printf("%d\n", v->a);
  printf("%p\n", v->b);

  *v = a;

  printf("%d\n", v->a);
  printf("%p\n", v->b);

  return v;
}

char *bar()
{
  int i = 10;
  printf("i  =%p\n", &i);

  void *k = malloc(sizeof(void *));
  /* void *k; */
  printf("&k =%p\n", &k);
  printf("k  =%p\n", k);

  char *a = "abcd";
  printf("a  =%p\n", &a);
  printf("a+0=%p\n", a + 0);
  printf("a+1=%p\n", a + 1);
  printf("a+2=%p\n", a + 2);

  return a;
}

int *baz()
{
  int a[] = {100, 200, 300};
  /* int *b = {100, 200, 300}; */

  printf("a=%p\n", &a);
  printf("a=%p\n", &a[0]);

  /* printf("b=%p\n", &b); */
  /* printf("b=%d\n", &b[0]); */

  return a;
}

int main(int argc, char *argv[])
{
  char ff[] = "asfas";
  *(ff + 1) = 'b';
  printf("%p\n", &ff[0]);
  printf("%p\n", &ff[1]);
  printf("%p\n", &ff[2]);
  printf("%p\n", &ff[3]);
  printf("%p\n", &ff);
  printf("%p\n", ff);

  /* atype *a = foo(); */

  /* int fff = 0; */
  /* printf("fff=%p\n", &fff); */

  /* char *b = bar(); */
  /* printf("b  =%p\n", b) ; */

  int *a = baz();
  printf("%d\n", a[0]);
  printf("%d\n", a[1]);
  printf("%d\n", a[2]);

  /* printf("%d\n", a->a); */
  /* printf("%p\n", a->b); */
  return 0;
}
