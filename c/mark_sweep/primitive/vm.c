#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

vm* new_vm()
{
  vm* vm = malloc(sizeof(vm));
  vm->stack_size = 0;

  vm->heap = malloc(HEAP_SIZE);
  vm->next = vm->heap;

  object* o = (object*)vm->heap;
  vm->next += OBJ_SIZE;
  o->size = HEAP_SIZE - OBJ_SIZE;
  o->marked = 0;
  o->body = vm->next;
  vm->freelist = o;

  return vm;
}

void free_vm(vm* vm)
{
  free(vm->heap);
  free(vm);
}

void assert_live(vm* vm, int expected_count) {
  int actual_count = 0;
  void* o = (object*)vm->heap;

  while (o < (vm->heap + HEAP_SIZE)) {
    if (((object*)o)->type != OBJ_FREE) {
      actual_count += 1;
    }
    o += ((object*)o)->size;
  }

  if (actual_count == expected_count) {
    printf("PASS: Expected and found %d live objects.\n", expected_count);
  } else {
    printf("Expected heap to contain %d objects, but had %d.\n",
           expected_count, actual_count);
    exit(1);
  }
}

void* heap_end(vm* vm)
{
  return vm->heap + HEAP_SIZE;
}

object* split_heap(object* obj, size_t size)
{
  object* o = NULL;

  /* split */
  object* next = obj->body;
  next += size;

  /* new object */
  o = next;
  next += OBJ_SIZE;
  o->size = obj->size - OBJ_SIZE;
  o->body = next;

  return o;
}

object* pickup_object(vm* vm, size_t size)
{
  object* pre = NULL;
  object* freelist = vm->freelist;

  while (freelist->size < size) {
    if (freelist->body == NULL)  {
      perror("out of memory");
      exit(1);
    } else {
      pre = freelist;
      freelist = freelist->body;
    }
  }

  if (pre == NULL) {            /* found allocate memory at first of freelist */
    if (freelist->size == size) {
      vm->freelist = freelist->body;
    } else {
      vm->freelist = split_heap(freelist, size);
    }
  } else {
    if (freelist->size == size) {
      pre->body = freelist->body;
    } else {
      pre->body = split_heap(freelist, size);
    }
  }
  return freelist;
}

object* new_int_object(vm* vm)
{
  object* object = pickup_object(vm, O_INT_SIZE);
  object->marked = 0;
  object->type = OBJ_INT;
  object->size = O_INT_SIZE;
  return object;
}

object* pop(vm* vm)
{
  return vm->stack[--vm->stack_size];
}

void push(vm* vm, object* obj)
{
  vm->stack[vm->stack_size++] = obj;
}

void push_int(vm* vm, int value)
{
  object* object = new_int_object(vm);
  ((o_int*)object->body)->value = value;

  push(vm, object);
}
