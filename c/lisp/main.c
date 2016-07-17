#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "mlisp.h"
#include "parse.h"
#include "debug.h"

#define MEMORY_SIZE 65536

typedef struct objspace_t {
  /* unused heap size */
  size_t mem_unsed;

  /* memory heap */
  void* memory;

} objspace_t;

static objspace_t *space;

static void *allocate_space()
{
  return mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
}

static void *new_objspace()
{
  space = malloc(sizeof(objspace_t));
  if (space == NULL)
    return NULL;

  space->memory = allocate_space();
  space->mem_unsed = 0;

  return space;
}

static obj_t *alloc(type_t type, size_t size)
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

static obj_t *make_int(int value)
{
  obj_t *obj = alloc(TINT, sizeof(int));
  obj->value = value;
  return obj;
}

static int get_env_flag(char *name) {
    char *val = getenv(name);
    return val && val[0];
}


int main(int argc, char *argv[])
{
  if (get_env_flag("MLISP_TEST")) {
    ast_t *aast = parse();
    print_ast(aast);
    return 0;
  }

  space = new_objspace();

  obj_t *a = make_int(1);
  obj_t *b = make_int(2);
  obj_t *c = make_int(3);

  printf("%d\n", a->value);
  printf("%d\n", b->value);
  printf("%d\n", c->value);
  return 0;
}
