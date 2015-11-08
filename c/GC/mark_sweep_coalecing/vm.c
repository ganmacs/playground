#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "gc.h"

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
  o->type = OBJ_FREE;
  vm->freelist = o;

  return vm;
}

void free_vm(vm* vm)
{
  free(vm->heap);
  free(vm);
}

void assert_live(vm* vm, int expected_count)
{
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
  ret->type = OBJ_FREE;
  ret->body = next + OBJ_SIZE;

  return ret;
}

object* pickup_object(vm* vm, size_t size)
{
  object* pre = NULL;
  object* freelist = vm->freelist;

  printf("freelist size: %lu\n", freelist->size);
  printf("size: %lu\n", size + OBJ_SIZE);
  printf("freelist first: %lu\n", (void*)freelist - vm->heap);

  while (freelist->size < size + OBJ_SIZE) { /* freelist size is next object size */
    /* puts("saikou"); */
    if (freelist->body == NULL)  {
      gc(vm);
      freelist = vm->freelist;
      break;
    } else {
      pre = freelist;
      freelist = freelist->next;
    }
  }

  if (freelist->size == size) {
    if (pre == NULL) {          /* head of freelist */
      vm->freelist = freelist->body;
    } else {
      pre->body = freelist->body;
    }
  } else if(freelist->size > size) {
    if (pre == NULL) {          /* head of freelist */
      vm->freelist = split_heap(freelist, size);
    } else {
      pre->body = split_heap(freelist, size);
    }
  } else {
    return NULL;
  }

  freelist->body = freelist + OBJ_SIZE; /* actaul body */
  /* printf("pickup!!--freelist - vm->hepa--------%lu\n", (void*)freelist - vm->heap); */
  return freelist;
}

object* new_object(vm* vm, object_type type)
{
  size_t size = object_size(type);
  object* object = pickup_object(vm, size);
  if (object == NULL) {
    perror("out of memory");
    exit(1);
  }
  object->marked = 0;
  object->type = type;
  object->size = size;
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
  object* object = new_object(vm, OBJ_INT);
  ((o_int*)object->body)->value = value;
  push(vm, object);
}

object* push_pair(vm* vm)
{
  object* object = new_object(vm, OBJ_PAIR);
  ((o_pair*)object->body)->head = pop(vm);
  ((o_pair*)object->body)->tail = pop(vm);
  push(vm, object);
  return object;
}
