#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1024

typedef struct {
  int i;
  void* moveTo;
} Object;

typedef struct {
  void* heap;
  void* next;
} VM;

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));

  vm->heap = malloc(HEAP_SIZE);
  vm->next = vm->heap;
  return vm;
}

void gc(VM* vm) {
  // TODO implement
}

void* heap_limit(VM* vm) {
  return vm->heap + HEAP_SIZE;
}

void* next_heap(VM* vm) {
  return vm->next + sizeof(Object);
}

Object* newObject(VM* vm) {
  if (next_heap(vm) > heap_limit(vm)) {
    gc(vm);

    if (next_heap(vm) > heap_limit(vm)) {
      perror("Out of memory");
      exit(1);
    }
  }

  Object* o = (Object*)vm->next;
  vm->next += sizeof(Object);

  o->moveTo = NULL;
  return o;
}

Object* newObject2(int i)
{
  Object* o = malloc(sizeof(Object));
  o->i = i;
  return o;
}

void print_object(Object* o)
{
  printf("addr = %p, i = %i, marked= %i\n", o, o->i, o->marked);
}

void print_array(Object* objs[]) {
  int i = 0;
  printf("{\n");
  while(objs[i]) {
    printf("   id: %d => ", i);
    print_object(objs[i]);
    i++;
  }
  printf("}\n");
}

void test1() {

}

void copy_test() {
  Object* from[10];
  Object* to[10];

  Object* o3 = newObject2(-1);
  Object* o4 = newObject2(2);
  Object* o5 = newObject2(-1);
  Object* o6 = newObject2(2);
  Object* o7 = newObject2(-1);
  from[0] = o3;
  from[1] = o4;
  from[2] = o5;
  from[3] = o6;
  from[4] = o7;
  print_array(from);

  for (int i = 0; i < 5; i++) {
    if (from[i]->i < 0) from[i]->marked = 1;
    i++;
  }

  for (int i = 0; i < 5; i++) {
    if (from[i]->i < 0) from[i]->marked = 1;
    i++;
  }
}

int main(int argc, char *argv[])
{
  VM* vm = newVM();
  printf("%p\n", vm->next);
  printf("%p\n", vm->next + sizeof(int));
  printf("%d\n", (int)sizeof(int));

  Object* o1 = newObject2(1);
  Object* o2 = newObject2(2);
  printf("Adress of a1 = %p and a2 = %p\n", o1, o2);
  printf("%d", (o1 + sizeof(Object))->i);

  //  copy_test();
  test1();
}
