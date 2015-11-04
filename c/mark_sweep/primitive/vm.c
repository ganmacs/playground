#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

vm* new_vm()
{
  vm* vm = malloc(sizeof(vm));
  vm->stack_size = 0;
  vm->root_size = 0;

  vm->heap->head = malloc(HEAP_SIZE);
  vm->heap->next = NULL;
  /* vm->next = vm->heap->head; */
  /* vm->freeList = vm->heap->head; */

  return vm;
}

void free_vm(vm* vm)
{
  free(vm->heap);
  free(vm);
}

int count_live(object* obj)
{
  switch(obj->type) {
  case OBJ_INT:
    return 1;
  case OBJ_PAIR:
    return count_live(((o_pair*)obj->body)->head) + count_live(((o_pair*)obj->body)->tail);
  }
}

void assert_live(vm* vm, int expected_count) {
  int actual_count = 0;
  for (int i = 0; i < vm->root_size; i++) {
    actual_count += count_live(vm->roots[i]);
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

object* new_int_object(vm* vm)
{

  object* object = (object*)vm->heap->next;
  object->marked = 0;
  vm->heap->next += OBJ_SIZE;
  object->type = OBJ_INT;

  object->body = (o_int*)vm->heap->next;
  vm->heap->next += O_Int_SIZE;

  /* vm->freeList += */
  return object;
  /* if (vm->next + OBJ_INT_SIZE > heapEnd(vm)){ */
  /* gc(vm) */
  /* } */

  /* Object* object = (Object*)vm->next; */
  /* object->marked = 0; */
  /* vm->next += OBJ_SIZE; */
  /* vm->freeList += OBJ_SIZE; */
  /* object->type = OBJ_INT; */

  /* object->body = (O_Int*)vm->next; */
  /* vm->freeList += O_Int_SIZE; */
  /* return object; */


}

object* pop(vm* vm)
{
  return vm->stack[--vm->stack_size];
}

void push(vm* vm, object* obj)
{
  vm->roots[vm->root_size++] = obj; /* for assersion */
  vm->stack[vm->stack_size++] = obj;
}

void push_int(vm* vm, int value)
{
  object* object = new_int_object(vm);
  ((o_int*)object->body)->value = value;

  push(vm, object);
}
