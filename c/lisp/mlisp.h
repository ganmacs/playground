#ifndef MLISP_H
#define MLISP_H

typedef struct obj_t {
  /* type of object */
  int type;

  /* size of object */
  int size;

  /* actual value of object */
  union {
    int value;
  };
} obj_t;

typedef enum {
  TINT = 1,
} type_t;

#endif
