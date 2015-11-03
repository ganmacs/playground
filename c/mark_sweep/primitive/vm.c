#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;

  vm->heap = malloc(HEAP_SIZE);
  vm->next = vm->heap;

  return vm;
}

void freeVM(VM* vm)
{
  free(vm->heap);
  free(vm);
}

int countLive(Object* obj)
{
  switch(obj->type) {
  case OBJ_INT:
    return 1;
  case OBJ_PAIR:
    return countLive(((O_Pair*)obj->body)->head) + countLive(((O_Pair*)obj->body)->tail);
  }
}

void assertLive(VM* vm, int expectedCount) {
  int actualCount = 0;
  for (int i = 0; i < vm->stackSize; i++) {
    actualCount += countLive(vm->roots[i]);
  }

  if (actualCount == expectedCount) {
    printf("PASS: Expected and found %d live objects.\n", expectedCount);
  } else {
    printf("Expected heap to contain %d objects, but had %d.\n",
           expectedCount, actualCount);
    exit(1);
  }
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
  vm->roots[vm->stackSize++] = obj; /* for assersion */
  vm->stack[vm->stackSize++] = obj;
}

void pushInt(VM* vm, int value)
{
  Object* object = newIntObject(vm);
  ((O_Int*)object->body)->value = value;

  push(vm, object);
}
