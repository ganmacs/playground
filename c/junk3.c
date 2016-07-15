#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct Obj {
  int type;
  int type2;

  union {
    int value;
    char name[1];
  };
} Obj;

void t_gchar()
{
  int c = getchar();
  printf("%c\n", c);
}

void t_off()
{
  printf("%d\n", (int)sizeof(char));
  printf("%d\n", (int)offsetof(Obj, type));
  printf("%d\n", (int)offsetof(Obj, type2));
  printf("%d\n", (int)offsetof(Obj, value));
  printf("%d\n", (int)offsetof(Obj, name));
}

size_t roundup(size_t var, size_t size)
{
  return (var + size - 1) & ~(size - 1);
}

void t_round()
{
  /* printf("%x\n", ~7); */
  /* printf("%x\n", ~0); */
  /* printf("%x\n", ~1); */
  /* printf("%x\n", ~2); */
  /* printf("%d\n", ~3 & (3 + 10)); */

  printf("%lu\n", roundup(9, 4));
  printf("%lu\n", roundup(10, 4));
  printf("%lu\n", roundup(11, 4));
  printf("%lu\n", roundup(12, 4));
  printf("%lu\n", roundup(13, 4));
  printf("%lu\n", roundup(14, 4));
}

void t_union()
{
  Obj *o = malloc(sizeof(Obj));
  o->value = 10;
  printf("%d\n", o->value);

  strcpy(o->name, "a");

  printf("%d\n", o->value);
}

int main(int argc, char *argv[])
{
  t_round();
  /* t_union(); */
  /* t_off(); */
  /* t_gchar(); */
  return 0;
}
