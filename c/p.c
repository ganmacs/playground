#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexDump(char *desc, void *addr, int len)
{
  int i;
  unsigned char buff[17];
  unsigned char *pc = (unsigned char*)addr;

  // Output description if given.
  if (desc != NULL)
    printf ("%p:%s:\n", addr, desc);

  // Process every byte in the data.
  for (i = 0; i < len; i++) {
    // Multiple of 16 means new line (with line offset).

    if ((i % 16) == 0) {
      // Just don't print ASCII for the zeroth line.
      if (i != 0)
        printf("  %s\n", buff);

      // Output the offset.
      printf("  %04x ", i);
    }

    // Now the hex code for the specific character.
    printf(" %02x", pc[i]);

    // And store a printable ASCII character for later.
    if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
      buff[i % 16] = '.';
    } else {
      buff[i % 16] = pc[i];
    }

    buff[(i % 16) + 1] = '\0';
  }

  // Pad out last line if not exactly 16 characters.
  while ((i % 16) != 0) {
    printf("   ");
    i++;
  }

  // And print the final ASCII bit.
  printf("  %s\n", buff);
}
typedef struct obj_t {
  char *name;
  int value;
} obj_t;


obj_t *create()
{
  obj_t *hoge = (obj_t *)malloc(sizeof(obj_t *));

  hoge->name = strdup("foo");
  hoge->value = 10;
  return hoge;
}

obj_t *create2()
{
  obj_t *hoge = (obj_t *)malloc(sizeof(obj_t));

  hoge->name = strdup("foo");
  hoge->value = 10;
  return hoge;
}

void check()
{
  /* obj_t *hoge = malloc(sizeof(obj_t)); */
  /* obj_t *hoge2 = malloc(sizeof(obj_t *)); */

  /* printf("%p\n", hoge); */
  /* printf("%p\n", &(hoge->name)); */
  /* printf("%p\n", &(hoge->value)); */

  /* printf("%p\n", hoge2); */
  /* hoge2->value = 10; */
  /* printf("%p\n", &(hoge2->name)); */
  /* printf("%p\n", &(hoge2->value)); */

  /* obj_t *ret = create(); */
  /* printf("%p\n", ret); */
  /* printf("%p\n", &(ret->name)); */
  /* printf("%p\n", &(ret->value)); */

  /* printf("%s\n", ret->name); */
  /* printf("%d\n", ret->value); */
  /* free(ret); */
}

char *str_create()
{

  char *a = (char *)malloc(1);
  a = "a";
  return a;
}

#define N 15

void p_check()
{

  char *c;

  for (int i = 0; i < 10; i++) {
    c = (char *)malloc(1);

    for (int i = 0; i < N; i++) {
      if (N - 1 == i) {
        c[i] = '/';
      } else {
        c[i] = i + '0';
      }
    }
    /* c = "abasdfghjkl"; */
    hexDump("c", c - 16, 128);
    printf("%s\n", c);
  }

}

void p_check2()
{

  char *c = (char *)malloc(1);
  for (int i = 0; i < N; i++) {
    if (N - 1 == i) {
      c[i] = '/';
    } else {
      c[i] = i + 'a';
    }
  }

  hexDump("c", c - 16, 128);

  char *d = (char *)malloc(1);
  for (int i = 0; i < N; i++) {
    if (N - 1 == i) {
      d[i] = '/';
    } else {
      d[i] = i + 'a';
    }
  }

  hexDump("c", d - 16, 128);

  printf("%s\n", c);
  printf("%s\n", d);

}

int main(int argc, char *argv[])
{
  /* check(); */
  /* p_check(); */
  p_check2();
  return 0;
}
