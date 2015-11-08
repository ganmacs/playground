#include "gc.h"

#define OBJ_TYPE(o) (((object*)o)->type)
#define PAIR_HEAD(o) (((o_pair*)((object*)o)->body)->head)
#define PAIR_TAIL(o) (((o_pair*)((object*)o)->body)->tail)
#define OBJ_AND_BODY_SIZE(obj) (OBJ_SIZE + ((object*)obj)->size)
#define HEAP_END(vm) (vm->heap + HEAP_SIZE)

void mark(object* obj)
{
  if (obj->marked) return;
  obj->marked = 1;

  if (obj->type == OBJ_PAIR) {
    mark(PAIR_HEAD(obj));
    mark(PAIR_TAIL(obj));
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

  while (now < HEAP_END(vm)) {
    if (((object*)now)->marked) {
      ((object*)now)->marked = 0;          /* reset */
    } else {
      ((object*)now)->type = OBJ_FREE;
      ((object*)now)->body = vm->freelist;
      vm->freelist = now;
    }
    now += OBJ_AND_BODY_SIZE(now);
  }
}

void gc(vm* vm) {
  mark_all(vm);
  sweep(vm);
}
