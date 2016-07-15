#include <stdio.h>

#ifndef MLISP_H
#define MLISP_H

typedef struct Obj {
  /* type of object */
  int type;

  /* size of object */
  int size;

  /* actual value of object */
  union {
    int value;
  };
} Obj;

enum {
  TINT = 1,
};

#endif
