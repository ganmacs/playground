#include <stdio.h>
#include "vm.h"
#include "gc.h"

void test1()
{
  printf("Test 1: Objects on stack are preserved.\n");
  vm* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);

  assert_live(vm, 2);
  free_vm(vm);
}

void test2() {
  /* printf("Test 2: Unreached objects are collected.\n"); */
  /* vm* vm = new_vm(); */
  /* push_int(vm, 1); */
  /* push_int(vm, 2); */
  /* pop(vm); */
  /* pop(vm); */

  /* gc(vm); */
  /* assert_live(vm, 0); */
  /* free_vm(vm); */
}

int main(int argc, char *argv[])
{
  test1();
  /* test2(); */
  return 0;
}
