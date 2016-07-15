#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mlisp.h"

#define MEMORY_SIZE 65536

static void *memory;

static void *allocate_space() {
  return mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
}


int main(int argc, char *argv[])
{
  memory = allocate_space();

  return 0;
}
