#ifndef INCLUDE_VM_H

#include "object.h"

#define HEAP_SIZE 1024
#define STACK_SIZE 1024

typedef struct {
  Object* stack[STACK_SIZE];
  Object* roots[STACK_SIZE];    /* for assertion */
  int stackSize;

  void* heap;
  void* next;
} VM;

VM* newVM();
void freeVM(VM* vm);

void assertLive(VM* vm, int expectedCount);

void push(VM* vm, Object* obj);
void pushInt(VM* vm, int value);
Object* pop(VM* vm);

#define INCLUDE_VM_H
#endif
