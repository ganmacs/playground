#ifndef H1
#define H1
#include <stdio.h>

typedef struct obj_t {
  int value;
} obj_t;

obj_t *NIL = &(obj_t) { 1 };

#include "debug.h"
#include "debug2.h"

#endif
