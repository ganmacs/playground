#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "debug.h"
#include "gc.h"
#include "mlisp.h"
#include "parse.h"
#include "util.h"
/* #include "eval.h" */

obj_t *NIL = &(obj_t) { TNIL };

static int get_env_flag(char *name) {
  char *val = getenv(name);
  return val && val[0];
}

obj_t *eval(env_t *env, obj_t* obj);

obj_t *eval_list(env_t *env, obj_t* obj)
{
  obj_t *head = NIL;
  for (;obj != NIL; obj = obj->cdr) {
    head = make_cell(eval(env, obj->car), head);
  }
  return head;
}

obj_t *find_variable(env_t *env, char *name)
{
  for (; env != NULL; env = env->next) {
    if (!strcmp(env->name, name))
      return env->val;
  }
  return NULL;
}

obj_t *apply(env_t *env, obj_t *fn, obj_t *args)
{
  if (args == NULL && args->type != TCELL)
    error("Must be a list at arguments of function");

  return fn->fn(env, args);
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

env_t *new_env(obj_t *val, char* name, env_t *old_env)
{
  env_t *env = malloc(sizeof(env_t));
  env->val = val;
  if (name == NULL) {
    env->name = NULL;
  } else {
    env->name = strdup(name);
  }
  env->next = old_env;
  return env;
}

env_t *init_env()
{
  return new_env(NULL, NULL, NULL);                  /* FIX */
}

void destroy_env(env_t *env)
{
  while (env != NULL) {
    /* TODO fix that obj_t is leaking */
    env_t *next = env->next;
    free(env);
    env = next;
  }
}

obj_t *prim_plus(env_t *env, obj_t *list)
{
  int sum = 0;

  for (obj_t *args = eval_list(env, list); args != NIL; args = args->cdr) {
    if (args->car->type != TINT)
      error("Requre int value");
    sum += args->car->value;
  }
  return make_int(sum);
}

void add_variable(env_t **env, char *name, obj_t *var)
{
  *env = new_env(var, name, *env);
}

void add_primitive(env_t **env, char *name, primitive_t *fn)
{
  obj_t *prim = make_primitive(fn);
  add_variable(env, name, prim);

}

void define_primitives(env_t **env)
{
  add_primitive(env, "+", prim_plus);
}

int main(int argc, char *argv[])
{
  if (get_env_flag("MLISP_PARSE_TEST")) {
    ast_t *ast = parse();
    print_ast(ast);
    destory_ast(ast);
  }

  if (get_env_flag("MLISP_EVAL_TEST")) {
    init_gc();
    env_t *env = init_env();
    ast_t *ast = parse();
    obj_t *obj = static_allocation(ast);

    define_primitives(&env);
    print_obj(eval(env, obj));
    destory_ast(ast);
    destroy_env(env);
  }

  return 0;
}
