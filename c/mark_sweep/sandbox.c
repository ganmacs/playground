#include <stdio.h>
#include <stdlib.h>

typedef struct sObject {
  struct sObject* next;
  int v;
} Object;

typedef struct vm {
  Object* firstObject;
} VM;

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->firstObject = NULL;
  return vm;
}

void newObject(VM* vm, int value)
{
  Object* object = malloc(sizeof(Object));
  object->v = value;

  object->next = vm->firstObject;
  vm->firstObject = object;
  /* printf("%d\n" ,vm->firstObject->v); */
}

void traverse(VM* vm)
{
  Object* object = vm->firstObject;

  while (object) {
    printf("%d\n", object->v);
    object = object->next;
    puts("----");
  }
}

void traverse2(VM* vm)
{
  Object** object = &vm->firstObject;

  while (*object) {
    printf("%d\n", (*object)->v);
    object = &(*object)->next;
    puts("----");
  }
}

void test2() {
  void* ary[10];
  int* i = malloc(sizeof(int));
  char* c = malloc(sizeof(char));

  ary[0] = i;
  ary[1] = c;
}

typedef struct
{
  int size;
  int type;
} Obj;

int main(int argc, char *argv[])
{

  VM* vm = newVM();
  /* newObject(vm, 0); */
  /* newObject(vm, 1); */
  /* newObject(vm, 2); */
  /* traverse(vm); */
  test2();

  void* heap = malloc(1000);
  int a = (int)heap;
  a = 10;
  heap += sizeof(int);
  printf("%d\n", a);
  printf("%d\n", (int)sizeof(int));
  printf("%d\n", (int)sizeof(Obj));
  printf("%d\n", (int)sizeof(void));
  printf("%d\n", (int)sizeof(char));

  /* Object* object = malloc(sizeof(Object)); */
  /* Object* o = object; */

  /* if (o) { */
  /*   printf("allocated"); */
  /* } */


  /* int* p; */
  /* int a; */
  /* a = 10; */
  /* p = &a; */
  /* printf("%d", *p); */
  /* int s = 10; */
  /* int s2 = 1; */
  /* int* p = &s; */
  /* int** q = &p; */
  /* p = &s; */
  /* q = &p; */
  /* printf("%p\n", p); */
  /* printf("%d\n", **q); */
  /* p = &s2; */
  /* printf("%d\n", **q); */
  return 0;
}
