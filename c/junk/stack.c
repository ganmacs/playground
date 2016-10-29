#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* typedef struct obj_t { */
/*   char* name; */
/* } obj_t; */

/* static void *END = -1; */

#define END (void *) -1

void printer2(void *root)
{
  void **frame = root;
  /* printf("%p\n", root[0]); */
  /* printf("%p\n", root[0]); */
  /* printf("%p\n", root[0]); */


  /* printf("%p\n", frame[0]); */
  /* printf("%p\n", frame[1]); */
  /* printf("%p\n", frame[2]); */

  for (int i = 1; frame[i] != END; i++) {
    printf("%d\n", (int)frame[i]);
  }
}


void foo(void *root, int *k)
{
  void *ary[3];
  ary[0] = root;
  int *v = (int *)(ary + 1);    /* Does it need to be more pointers? */
  printf("%p\n", ary + 1);
  v = k;

  /* printf("v=%p\n", *v); */
  printf("v=%p\n", *(ary + 1));

  ary[2] = END;
  root = ary;

  printf("ary   =%p\n", ary);
  printf("ary+1 =%p\n", ary + 1);
  printf("ary+2 =%p\n", ary + 2);
  printf("root  =%p\n", root);

  printf("%d\n", (int)ary[1]);
  printf("%d\n", (int)ary[2]);

  printer2(root);
}

void nu()
{
  int *a[4];
  for (int i = 0; i < 4; i++) {
    printf("%p\n", a[i]);
  }

  printf("%p\n", (void *)0);
  printf("%p\n", NULL);
}

void bar()
{
  int *a[4];
  int v = 10;
  a[0] = &v;
  a[1] = &v;                    /* init */
  a[2] = &v;                    /* init */

  int *empty = a[1];
  int k = 100;
  empty = &k;

  printf("a[1] =%p\n", a[1]);
  printf("empty=%p\n", empty);

  int **my = (int **)(a + 2);
  int **my2 = (int **)a[2];
  printf("my   =%p\n", my);
  printf("my2  =%p\n", my2);

  puts("\n===================================== start print");
  printf("=%p\n", (int **)(a + 0));
  printf("=%p\n", (int **)(a + 1));
  printf("=%p\n", (int **)(a + 2));

  printf("=%p\n", &a[0]);
  printf("=%p\n", &a[1]);
  printf("=%p\n", &a[2]);
  puts("\n===================================== finish print");

  *my = &k;

  printf("a[2]=%p\n", a[2]);
  printf("my  =%p\n", my);

  printf("a[2]=%d\n", *a[2]);
  printf("a[2]=%d\n", **my);

  for (int i = 0; i < 3; i++) {
    printf("%d\n", *a[i]);
  }
}
void baz()
{

  int *ary[3];
  int v = 10;

  ary[0] = &v;
  ary[1] = &v;
  ary[2] = &v;

  /* printf("%p\n", ary + 1); */
  /* printf("%p\n", ary); */

  int **k = (ary + 1);
  int v2 = 100;
  printf("%p\n", k);
  printf("%p\n", ary + 1);

  printf("%d\n", **k);
  printf("%d\n", **(ary + 1));

  *k = &v2;

  printf("%p\n", k);
  printf("%p\n", ary + 1);

  printf("%d\n", **k);
  printf("%d\n", **(ary + 1));

  for (int i = 0; i < 3; i++) {
    printf("%p\n", ary[i]);
  }
}

void p(int *v)
{
  printf("%p\n", v);
  *v = 10;
}

void p2(int v)
{
  printf("%p\n", &v);
  v = 15;
}

void printer(void *root)
{
  void **frame = root;

  if (frame == NULL) {
    puts("No tree remains");
    return;
  }

  for (void **frame = root; frame != NULL; frame = *frame) {
    for (int i = 1; frame[i] != END; i++) {
      int* v = frame[i];
      printf("%d\n", *v);
    }
  }
}

void saikou3(void *root, int *v)
{
  void *ary[3];
  ary[0] = root;
  ary[1] = v;
  ary[2] = END;
  root = ary;
  printer(root);
}


void saikou2(void *root, int *v)
{
  void *ary[4];
  ary[0] = root;
  ary[1] = v;
  ary[2] = v;
  ary[3] = END;
  root = ary;

  int k = 1000;
  saikou3(root, &k);

  puts("\n===================================== start print");

  printer(root);
}

void saikou(void *root, int *v)
{
  void *ary[3];
  ary[0] = root;
  ary[1] = v;
  ary[2] = END;
  root = ary;

  int k = 100;
  saikou2(root, &k);
}

int main()
{
  /* obj_t *root = malloc(sizeof(obj_t*)); */
  /* root->name = "name space"; */

  void *root = NULL;
  int v = 10;
  /* foo(root, &v); */

  /* bar(); */

  /* int v = 1; */
  /* printf("%p in main\n", &v); */
  /* p(&v); */
  /* printf("%p in main\n", &v); */
  /* p2(v); */
  /* printf("%p in main\n", &v); */
  /* printf("%d\n", v); */
  /* baz(); */

  saikou(root, &v);
  printer(root);

  return 0;
}
