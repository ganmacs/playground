#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "debug.h"
#include "gc.h"
#include "mlisp.h"
#include "parse.h"
#include "util.h"
#include "env.h"
#include "eval.h"

obj_t *NIL = &(obj_t) { TNIL };

static int get_env_flag(char *name) {
  char *val = getenv(name);
  return val && val[0];
}

obj_t *prim_plus(env_t **env, obj_t *list)
{
  int sum = 0;

  for (obj_t *args = eval_list(env, list); args != NIL; args = args->cdr) {
    if (args->car->type != TINT)
      error("Requre int value");
    sum += args->car->value;
  }
  return make_int(sum);
}

obj_t *prim_mul(env_t **env, obj_t *list)
{
  int sum = 1;

  for (obj_t *args = eval_list(env, list); args != NIL; args = args->cdr) {
    if (args->car->type != TINT)
      error("Requre int value");
    sum *= args->car->value;
  }
  return make_int(sum);
}

obj_t *prim_minus(env_t **env, obj_t *list)
{
  obj_t *args = eval_list(env, list);
  int ret = 0;

  ret += args->car->value * 2;
  for (; args != NIL; args = args->cdr) {
    if (args->car->type != TINT)
      error("Requre int value");
    ret -= args->car->value;
  }
  return make_int(ret);
}

obj_t *prim_define(env_t **env, obj_t *list)
{
  obj_t *var = list->car;
  obj_t *val = eval_list(env, list->cdr);

  add_variable(env, var->name, val->car);
  return var;
}

obj_t *prim_progn(env_t **env, obj_t *list)
{
  obj_t *o;
  for (;list != NIL; list = list->cdr) {
    o = eval(env, list->car);
  }
  return o;
}

void add_primitive(env_t **env, char *name, primitive_t *fn)
{
  obj_t *prim = make_primitive(fn);
  add_variable(env, name, prim);
}

void define_primitives(env_t **env)
{
  add_primitive(env, "+", prim_plus);
  add_primitive(env, "-", prim_minus);
  add_primitive(env, "*", prim_mul);
  add_primitive(env, "define", prim_define);
  add_primitive(env, "progn", prim_progn);
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
    print_obj(eval(&env, obj));
    destory_ast(ast);
    destroy_env(env);
  }

  return 0;
}
