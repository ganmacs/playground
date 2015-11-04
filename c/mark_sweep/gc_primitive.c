#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1024
#define STACK_SIZE 1024
#define OBJ_SIZE sizeof(Object)
#define O_Int_SIZE sizeof(O_Int)
#define O_Pair_SIZE sizeof(O_Pair)
#define OBJ_INT_SIZE (O_Int_SIZE + OBJ_SIZE)
#define OBJ_PAI_SIZE (O_Pair_SIZE + OBJ_SIZE)

/* data type */
typedef enum {
  OBJ_INT,
  OBJ_PAIR
} ObjectType;

typedef struct {
  /* header info */
  /* int size; */
  ObjectType type;

  /* actual data */
  void* body;
} Object;

typedef struct {
  int value;
} O_Int;

typedef struct {
  Object* head;
  Object* tail;
} O_Pair;

typedef struct {
  Object* stack[STACK_SIZE];
  int stackSize;

  void* heap;
  void* next;
} VM;

int countLive(Object* obj)
{
  switch(obj->type) {
  case OBJ_INT:
    return 1;
  case OBJ_PAIR:
    return countLive(((O_Pair*)obj->body)->head) + countLive(((O_Pair*)obj->body)->tail);
  }
}

void assertLive(VM* vm, long expectedCount) {
  int actualCount = 0;
  for (int i = 0; i < vm->stackSize; i++) {
    actualCount += countLive(vm->stack[i]);
  }

  if (actualCount == expectedCount) {
    printf("PASS: Expected and found %ld live objects.\n", expectedCount);
  } else {
    printf("Expected heap to contain %ld objects, but had %ld.\n",
           expectedCount, (long)actualCount);
    exit(1);
  }
}

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;

  vm->heap = malloc(HEAP_SIZE);
  vm->next = vm->heap;

  return vm;
}

void* heapEnd(VM* vm)
{
  return vm->heap + HEAP_SIZE;
}


Object* newIntObject(VM* vm)
{
  if (vm->next + OBJ_INT_SIZE > heapEnd(vm)){
    /* gc(vm) */
  }

  Object* object = (Object*)vm->next;
  vm->next += OBJ_SIZE;
  object->type = OBJ_INT;

  object->body = (O_Int*)vm->next;
  vm->next += O_Int_SIZE;
  return object;
}

Object* pop(VM* vm)
{
  return vm->stack[--vm->stackSize];
}

void push(VM* vm, Object* obj)
{
  vm->stack[vm->stackSize++] = obj;
}

void pushInt(VM* vm, int value)
{
  Object* object = newIntObject(vm);
  ((O_Int*)object->body)->value = value;

  push(vm, object);
}

void freeVM(VM* vm)
{
  free(vm->heap);
  free(vm);
}

void test1()
{
  printf("Test 1: Objects on stack are preserved.\n");
  VM* vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);

  assertLive(vm, 2);
  freeVM(vm);
}

int main(int argc, char *argv[])
{
  test1();
  return 0;
}
