#include <stdio.h>
#include <stdlib.h>

typedef struct foo {
  int type;
  /* char c; */
  /* char c1; */
  /* char c2; */
  /* char c3; */
  /* char c4; */
  void *ptr;
} foo;


static char *a = "abcd";
static foo *f = &(foo){ 2 };
static foo *k = &(foo){ 3 };

int main(int argc, char *argv[])
{
  /* printf("f=        %p\n", f); */
  /* printf("&f->type= %p\n", &f->type); */
  /* printf("&f->c=    %p\n", &f->c); */
  /* printf("&f->ptr=  %p\n", &f->ptr); */

  /* printf("%lu\n", sizeof(struct foo)); */


  /* printf("%d\n", f->type); */

  foo *l = malloc(sizeof(foo));
  printf("l=%p\n", l);
  printf("f=%p\n", f);
  printf("k=%p\n", k);

  /* printf("%s\n", a); */
  /* printf("%p\n", a); */
  /* for (int i = 0; i < 4; i++) { */
  /*   printf("%p\n", &a[i]); */
  /*   printf("%c\n", a[i]); */
  /* } */

  return 0;
}
