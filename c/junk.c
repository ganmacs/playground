#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void a(void* v)
{
  printf("%d\n", ((int*)v)[0]);
  printf("%d\n", *((int *) v) - '0');
}

void pcp(char* a)
{
  printf("%p\n", a);
}

void ps(char a[])
{
  printf("%p\n", a);
}


void mpoi()
{

  char a1[] = "a";
  char* a2 = "a";

  printf("%p\n", a1);
  printf("%p\n", a2);
  printf("%p\n", "a");

  ps(a1);
  pcp(a1);
  ps(a2);
  pcp(a2);
  printf("%p\n", "a");

  /* a = malloc(sizeof(char*) * 5); */

  /* printf("%p\n", a[0]); */
  /* printf("%p\n", a[1]); */
  /* printf("%p\n", a[2]); */
  /* printf("%p\n", a[3]); */
  /* printf("%p\n", a[4]); */

  /* printf("%s\n", a[0]); */
  /* printf("%s\n", a[1]); */
  /* printf("%s\n", a[2]); */
  /* printf("%s\n", a[3]); */
  /* printf("%s\n", a[4]); */

  /* char* a[] = {"asdf", "Asdf", "asfd"}; */

  /* printf("%s\n", a[0]); */
  /* printf("%s\n", a[1]); */
  /* printf("%s\n", a[2]); */

  /* printf("%p\n", a); */
  /* printf("%p\n", a[0]); */
  /* printf("%p\n", a[1]); */
  /* printf("%p\n", a[2]); */

  /* a = { "", "", "" }; */

  /* a = malloc(sizeof(char) * 10); */
  /* strcpy(a, "a"); */

  /* a[0] = 'c'; */

  /* printf("%p\n", "a"); */
  /* printf("%p\n", a); */

  /* printf("%s\n", a); */

  /* char** k; */

  /* k = malloc(sizeof(char)*4); */
  /* printf("%p\n", k); */
  /* printf("%p\n", k + 1); */

  /* k[0] = "abc"; */
  /* k[1] = "abc"; */

  /* char* b; */
  /* b = "asfadfasldfjadfkjadlfkjaldsfkja;dfjakdfa;ek"; */

  /* printf("%c\n", *(b + 0)); */
  /* printf("%c\n", *(b + 1)); */
  /* printf("%c\n", *(b + 2)); */
  /* printf("%c\n", *(b + 3)); */
  /* printf("%c\n", *(b + 4)); */
  /* printf("%c\n", *(b + 5)); */

}


int
main(int argc, char *argv[])
{
  mpoi();
  return 0;




  /* printf("void %d\n", (int)sizeof(void)); */
  /* printf("void* %d\n", (int)sizeof(void*)); */
  /* printf("int* %d\n", (int)sizeof(int*)); */

  char* b = "asdf";

  /* printf("%c\n", b[1]); */
  /* printf("%c\n", *(b + sizeof(char))); */

  /* printf("%d\n",(int) sizeof(char *)); */
  /* printf("%d\n",(int) sizeof(int *)); */
  /* printf("%d\n",(int) sizeof(void *)); */

  /* for (int i = 0; i < 128; i++) { */
  /*     printf("%c\n", i); */
  /* } */

  /* unsigned int c = 4294967295; */
  /* int *a = &c; */

  char* e = "as0df";
  /* e[3] = 'a'; */

  if ((int)'\0' == 0) {
    printf("%d\n", 10000);
  }

  /* printf("%s\n", e); */

  for (int i = 0; i < 5; i++) {
    printf("%c\n", e[i]);
  }


  /* printf("%d\n", *a + e[0]); */
  /* puts(""); */
  /* printf("%d\n", *(a + 0)); */


  printf("%u\n", -1);

  /* char dest[50]; */

  /* char src[10]; */

  /* for (int i = 0; i < 20; i++) { */
  /*   printf("%c\n", src[i]); */
  /* } */

  /* char src[10] = "asdf"; */
  /* char dest[10]; */
  /* printf("Before memcpy dest = %s\n", dest); */

  /* printf("%d\n", strlen(src)); */
  /* memcpy(dest, src, strlen(src)+1); */


  /* printf("After memcpy dest = %s\n", dest); */



  /* a("7"); */
  return 0;
}
