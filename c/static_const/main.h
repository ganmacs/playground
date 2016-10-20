#ifndef H1
#define H1

#include <stdio.h>
#include "debug.h"
#include "debug2.h"

typedef struct obj_t {
  int value;
} obj_t;

static obj_t *NIL = &(obj_t) { 1 };
#endif
