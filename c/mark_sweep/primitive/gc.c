#include "gc.h"

#define O(n) ((object*)n)
#define OBJ_TYPE(o) (O(o)->type)

void mark(object* obj)
{
  if (obj->marked) return;
  obj->marked = 1;

  if (obj->type == OBJ_PAIR) {
    mark(((o_pair*)obj->body)->head);
    mark(((o_pair*)obj->body)->tail);
  }
}

void mark_all(vm* vm)
{
  for (int i = 0; i < vm->stack_size; i++) {
    mark(vm->stack[i]);
  }
}

void sweep(vm* vm)
{
  void* now = vm->heap;

  while (now < vm->next) {
    if (O(now)->marked) {
      if (OBJ_TYPE(now) == OBJ_PAIR) {
        mark(((o_pair*)now->body)->head);
        mark(((o_pair*)now->body)->tail);
      }


      /* switch(OBJ_TYPE(now)) { */
      /* case OBJ_INT: */

      /*   break; */
      /* case OBJ_PAIR: */
      /*   break; */
      /* } */
    } else {
    }

    switch(OBJ_TYPE(now)) {
    case OBJ_INT:
      now += OBJ_INT_SIZE;
      break;
    case OBJ_PAIR:
      now += OBJ_PAIR_SIZE;
      break;
    }
  }
}

void gc(vm* vm) {
  mark_all(vm);
  sweep(vm);
}
