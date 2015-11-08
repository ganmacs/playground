#include <stdio.h>
#include "gc.h"

void test1()
{
  printf("## Test 1: Objects on stack are preserved.\n");
  vm* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);

  assert_live(vm, 2);
  free_vm(vm);
}

void test2() {
  printf("## Test 2: Unreached objects are collected.\n");
  vm* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  pop(vm);
  pop(vm);

  gc(vm);
  assert_live(vm, 0);
  free_vm(vm);
}

void test3() {
  printf("## Test 3: Reach nested objects.\n");
  vm* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  push_pair(vm);
  push_int(vm, 3);
  push_int(vm, 4);
  push_pair(vm);
  push_pair(vm);

  gc(vm);
  assert_live(vm, 7);
  free_vm(vm);
}

void test4() {
  printf("## Test 4: Handle cycles.\n");
  vm* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  object* a = push_pair(vm);
  push_int(vm, 3);
  push_int(vm, 4);
  object* b = push_pair(vm);

  ((o_pair*)b->body)->head = b;
  ((o_pair*)a->body)->tail = a;

  gc(vm);
  assert_live(vm, 4);
  free_vm(vm);
}

void test5() {
  printf("## Test 5: reuse object.\n");
  vm* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  pop(vm);
  pop(vm);
  gc(vm);

  push_int(vm, 3);
  push_int(vm, 4);


  assert_live(vm, 2);
  free_vm(vm);
}


void perfTest() {
  printf("## Performance Test.\n");
  vm* vm = new_vm();

  for (int i = 0; i < 2 ; i++) {
    for (int j = 0; j < 20; j++) {
      push_int(vm, i);
    }

    for (int k = 0; k < 20; k++) {
      pop(vm);
    }
  }
  free_vm(vm);
}


int main(int argc, char *argv[])
{
  test1();
  test2();
  test3();
  test4();
  test5();
  perfTest();
  return 0;
}
