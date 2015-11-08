#define OBJ_SIZE sizeof(object)
#define O_INT_SIZE sizeof(o_int)
#define O_PAIR_SIZE sizeof(o_pair)
#define OBJ_INT_SIZE (O_INT_SIZE + OBJ_SIZE)
#define OBJ_PAIR_SIZE (O__SIZE + OBJ_SIZE)

#include <stdio.h>

/* data type */
typedef enum {
  OBJ_FREE,
  OBJ_INT,
  OBJ_PAIR
} object_type;

typedef struct {
  /* header info */
  object_type type;
  int marked;
  size_t size;

  /* actual data */
  void* body;
} object;

typedef struct {
  int value;
} o_int;

typedef struct {
  object* head;
  object* tail;
} o_pair;
