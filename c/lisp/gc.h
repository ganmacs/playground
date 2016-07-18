#ifndef MLISP_GC_H
#define MLISP_GC_H

#include <stdio.h>
#include "mlisp.h"

void init_gc();

obj_t *static_allocation(ast_t *ast);

obj_t *make_int(int value);

obj_t *make_cell(obj_t *car, obj_t *cdr);

obj_t *make_symbol(char *name);

obj_t *make_primitive(primitive_t *prim);

#endif
