#include <stdio.h>
#include "vm.h"
#include "gc.h"

void test1()
{
  printf("Test 1: Objects on stack are preserved.\n");
  VM* vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);

  assertLive(vm, 2);
  freeVM(vm);
}

void test2() {
  printf("Test 2: Unreached objects are collected.\n");
  VM* vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);
  pop(vm);
  pop(vm);

  gc(vm);
  assertLive(vm, 0);
  freeVM(vm);
}

int main(int argc, char *argv[])
{
  test1();
  test2();
  return 0;
}
