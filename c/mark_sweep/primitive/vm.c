#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

#define OBJ_AND_BODY_SIZE(obj) (OBJ_SIZE + ((object*)obj)->size)
#define HEAP_END(vm) (vm->heap + HEAP_SIZE)

vm* new_vm()
{
  vm* vm = malloc(sizeof(vm));
  vm->stack_size = 0;

  vm->heap = malloc(HEAP_SIZE);
  vm->next = vm->heap;
  object* o = vm->heap;

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
  void* o = vm->heap;

  while (o < HEAP_END(vm)) {
    if (((object*)o)->type != OBJ_FREE) {
      actual_count += 1;
    }
    o += OBJ_AND_BODY_SIZE(o);
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

object* split_heap(object* obj, size_t first_size)
{
  void* next = obj->body;
  object* ret = NULL;

  next += first_size;

  ret = (object*)next;
  ret->size = obj->size - (OBJ_SIZE + first_size);
  next += OBJ_SIZE;
  ret->body = next;
  obj->size = first_size;

  return ret;
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
