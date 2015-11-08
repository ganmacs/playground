#pragma once

#include "object.h"

#define HEAP_SIZE 1024
#define STACK_SIZE 1024

typedef struct heap_ {
  object* head;
  object* next;
  /* struct heap_* nextHeap; */
} heap;

typedef struct {
  object* stack[STACK_SIZE];
  int stack_size;

  void* heap;
  void* next;
  object* freelist;
} vm;

vm* new_vm();
void free_vm(vm* vm);

void assert_live(vm* vm, int expected_count);

void push(vm* vm, object* obj);
void push_int(vm* vm, int value);
object* push_pair(vm* vm);
object* pop(vm* vm);
