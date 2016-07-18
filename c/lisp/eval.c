#include <stdio.h>
#include "eval.h"
#include "util.h"
#include "env.h"
#include "gc.h"

obj_t *reverse_list(obj_t* list)
{
  obj_t *head = NIL;

  while (list != NIL) {
    obj_t *next = list->cdr;
    list->cdr = head;
    head = list;
    list = next;
  }

  return head;
}

obj_t *eval_list(env_t *env, obj_t* obj)
{
  obj_t *head = NIL;
  for (;obj != NIL; obj = obj->cdr) {
    head = make_cell(eval(env, obj->car), head);
  }
  return reverse_list(head);
}

obj_t *apply(env_t *env, obj_t *fn, obj_t *args)
{
  if (args == NULL && args->type != TCELL)
    error("Must be a list at arguments of function");

  return fn->fn(env, args);     /* SEGMENTATION FAULT */
}

obj_t *eval(env_t *env, obj_t* obj)
{
  switch(obj->type) {
  case TNIL:
  case TINT:
  case TPRIMITIVE:
    return obj;
  case TSYMBOL: {
    obj_t *o = find_variable(env, obj->name);
    if (o == NULL) {
      printf("%s ", obj->name);
      error("Unkonw token");
    }
    return o;
  }
  case TCELL: {
    obj_t *fn = eval(env, obj->car);
    if (fn->type != TPRIMITIVE)
      error("Must be a function at head of list");

    return apply(env, fn, obj->cdr);;
  }
  }
}
