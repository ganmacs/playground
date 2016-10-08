#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *v = "abcde";

  printf("%c\n", v[0]);
  printf("%c\n", *(v + 1));
  printf("%s\n", v + 2);

  printf("%p\n", &v);
  printf("%p\n", v);
  printf("%p\n", &(v[1]));

  printf("addr_size: %zu\n", sizeof(void *));
  printf("char_size: %zu\n", sizeof(char));

  puts("------------------------------------------");

  void *foo = malloc(10 * sizeof(void *));
  printf("%p\n", foo);
  unsigned long addr_size = sizeof(void *);

  memcpy(foo, "abcdefg", addr_size);
  memcpy(foo + 8, "k2c3e4g", addr_size);

  printf("%s\n", foo);
  printf("%s\n", foo + 8);

  void **foobar = foo;

  printf("%c\n", foobar[0]);
  printf("%c\n", foobar[1]);

  /* printf("%zu\n", sizeof(double)); */

  double i[3] = {1.2, 2.3, 3.4};
  double **ii = i;

  printf("%p\n", ii);

  for (int i = 0; i < 3; i++) {
    printf("%f\n", ii);
  }

  /* printf("%f\n", *(i + 1)); */




  /* puts("\n=============================== start print"); */

  /* for (int i = 0; i < 10; i++) { */
  /*   printf("%p\n", foobar); */
  /*   printf("%s\n", foobar[i]); */
  /* } */

  return 0;
}
