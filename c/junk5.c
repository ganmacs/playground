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
  memcpy(foo + 8, "a2c3e4g", addr_size);

  printf("%s\n", foo);
  printf("%s\n", foo + 8);

  void **foobar = foo;

  puts("\n=============================== start print");

  for (int i = 0; i < 10; i++) {
    printf("%p\n", foobar);
    printf("%s\n", foobar[i]);
  }

  return 0;
}
