#include "object.h"

size_t object_size(object_type type)
{
  size_t size = 0;

  switch(type) {
  case OBJ_INT:
    size = O_INT_SIZE; break;
  case OBJ_PAIR:
    size = O_PAIR_SIZE; break;
  case OBJ_FREE:
    perror("error");
    exit(1);
  }

  return size;
}
