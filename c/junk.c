#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void a(void* v)
{
  printf("%d\n", ((int*)v)[0]);
  printf("%d\n", *((int *) v) - '0');
}

int
main(int argc, char *argv[])
{
  /* printf("void %d\n", (int)sizeof(void)); */
  /* printf("void* %d\n", (int)sizeof(void*)); */
  /* printf("int* %d\n", (int)sizeof(int*)); */

  char* b = "asdf";

  /* printf("%c\n", b[1]); */
  /* printf("%c\n", *(b + sizeof(char))); */

  /* printf("%d\n",(int) sizeof(char *)); */
  /* printf("%d\n",(int) sizeof(int *)); */
  /* printf("%d\n",(int) sizeof(void *)); */

  /* for (int i = -128; i < 128; i++) { */
  /*     printf("%c\n", i); */
  /* } */

  /* char dest[50]; */

  /* char src[10]; */

  /* for (int i = 0; i < 20; i++) { */
  /*   printf("%c\n", src[i]); */
  /* } */

  char src[10] = "asdf";
  char dest[10];
  printf("Before memcpy dest = %s\n", dest);

  printf("%d\n", strlen(src));
  memcpy(dest, src, strlen(src)+1);


  printf("After memcpy dest = %s\n", dest);

  a("7");
  return 0;
}
