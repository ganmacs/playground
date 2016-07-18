#include <stdlib.h>
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>
#include "gc.h"

#define MEMORY_SIZE 65536

typedef struct objspace_t {
  /* unused heap size */
  size_t mem_unsed;

  /* memory heap */
  void* memory;

} objspace_t;

/*
  DO NOT TOUCH THIS VARABLE UNLESS gc.c
*/
static objspace_t *space;

/*
  Create blank space in heap
*/
void *allocate_space()
{
  return mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
}

/*
  initailze object sapce
*/
void *new_objspace()
{
  space = malloc(sizeof(objspace_t));
  if (space == NULL)
    return NULL;

  space->memory = allocate_space();
  space->mem_unsed = 0;

  return space;
}

/*
  allocate value in heap
*/
obj_t *alloc(type_t type, size_t size)
{
  size += offsetof(obj_t, value);

  if (MEMORY_SIZE < space->mem_unsed + size) {
    perror("Memory exhausted");
    exit(1);
  }

  obj_t *obj = space->memory + space->mem_unsed;
  obj->type = type;
  obj->size = size;
  space->mem_unsed += size;
  return obj;
}

obj_t *make_symbol(char *name)
{
  obj_t *obj = alloc(TSYMBOL, sizeof(strlen(name) + 1));
  obj->name = strdup(name);
  return obj;
}

obj_t *make_int(int value)
{
  obj_t *obj = alloc(TINT, sizeof(int));
  obj->value = value;
  return obj;
}

obj_t *make_cell(obj_t *car, obj_t *cdr)
{
  obj_t *obj = alloc(TCELL, sizeof(obj_t) * 2);
  obj->car = car;
  obj->cdr = cdr;
  return obj;
}

obj_t *make_primitive(primitive_t *fn)
{
  obj_t *obj = alloc(TPRIMITIVE, sizeof(primitive_t *));
  obj->fn = fn;
  return obj;
}

void init_gc() {
  space = new_objspace();
}

/*
  memory allocation before running
*/
obj_t *static_allocation(ast_t *ast) {
  if (ast == NULL)
    return NIL;

  switch(ast->type) {
  case AST_CELL:
    return make_cell(static_allocation(ast->car), static_allocation(ast->cdr));
  case AST_SYMBOL:
    return make_symbol(ast->name);
  case AST_INT:
    return make_int(ast->value);
  }

  return NIL;
}
