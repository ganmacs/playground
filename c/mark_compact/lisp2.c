#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX 256
#define HEAP_SIZE (1024 * 1024)

typedef enum {
  OBJ_INT,
  OBJ_PAIR
} ObjectType;

typedef struct sObject {
  ObjectType type;

  void* moveTo;

  union {
    int value;

    struct {
      struct sObject* head;
      struct sObject* tail;
    };
  };
} Object;
#define O_SIZE sizeof(Object)

typedef struct {
  Object* stack[STACK_MAX];
  int stackSize;

  void* heap;
  void* next;
} VM;

void assertLive(VM* vm, long expectedCount)
{
  long actualCount = (vm->next - vm->heap) / O_SIZE;
  if (actualCount == expectedCount) {
    printf("PASS: Expected and found %ld live objects.\n", expectedCount);
  } else {
    printf("Expected heap to contain %ld objects, but had %ld.\n",
           expectedCount, actualCount);
    exit(1);
  }
}

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;

  vm->heap = malloc(HEAP_SIZE);
  vm->next = vm->heap;
  return vm;
}

int fulledStack(VM* vm)
{
  return vm->stackSize == STACK_MAX;
}

void* nextHeapPointer(VM* vm)
{
  return vm->next + O_SIZE;
}

void* maxHeapSize(VM* vm)
{
  return vm->heap + HEAP_SIZE;
}

void push(VM* vm, Object* obj)
{
  if (fulledStack(vm)) {
    perror("stack overflow\n");
    exit(1);
  }

  vm->stack[vm->stackSize++] = obj;
}

Object* pop(VM* vm)
{
  return vm->stack[--vm->stackSize];
}

void mark(Object* object)
{
  if (object->moveTo) return;

  /* assign not null value for recursion. */
  object->moveTo = object;

  if (object->type == OBJ_PAIR) {
    mark(object->head);
    mark(object->tail);
  }
}

void markAll(VM* vm)
{
  for (int i = 0; i < vm->stackSize; i++) {
    mark(vm->stack[i]);
  }
}

void* calculateNewLocations(VM* vm)
{
  void* from = vm->heap;
  void* to = vm->heap;

  while (from < vm->next) {
    Object* o = (Object*)from;

    /* check reachable object or not */
    if (o->moveTo) {
      o->moveTo = to;
      to += O_SIZE;
    }
    from += O_SIZE;
  }

  return to;
}

void updateAllObjectPointers(VM* vm)
{
  for (int i = 0; i < vm->stackSize; i++) {
    vm->stack[i] = vm->stack[i]->moveTo;
  }

  void* from = vm->heap;
  while (from < vm->next) {
    Object* o = (Object*)from;

    if (o->moveTo && o->type == OBJ_PAIR) {
      o->head = o->head->moveTo;
      o->tail = o->tail->moveTo;
    }

    from += O_SIZE;
  }
}

void compact(VM* vm)
{
  void* from = vm->heap;

  while (from < vm->next) {
    Object* o = (Object*)from;
    if (o->moveTo) {
      Object* to = o->moveTo;
      memmove(to, from, O_SIZE);
    }
    from += O_SIZE;
  }
}

void gc(VM* vm)
{
  markAll(vm);

  void* end = calculateNewLocations(vm);

  updateAllObjectPointers(vm);

  compact(vm);

  vm->next = end;

  printf("%ld live bytes after collection.\n", vm->next - vm->heap);
}

Object* newObject(VM* vm, ObjectType type)
{
  if (nextHeapPointer(vm) > maxHeapSize(vm)) {
    gc(vm);

    if (nextHeapPointer(vm) > maxHeapSize(vm)) {
      perror("Out of memory");
      exit(1);
    }
  }

  /* Allocate memory at vm heap */
  Object* object = (Object*)vm->next;
  vm->next += O_SIZE;

  object->moveTo = NULL;
  object->type = type;
  return object;
}

void pushInt(VM* vm, int intValue)
{
  Object* object = newObject(vm, OBJ_INT);
  object->value = intValue;
  push(vm, object);
}

Object* pushPair(VM* vm)
{
  Object* object = newObject(vm, OBJ_PAIR);
  object->tail = pop(vm);
  object->head = pop(vm);
  push(vm, object);

  return object;
}

void freeVM(VM* vm)
{
  free(vm->heap);
  free(vm);
}


void test1() {
  printf("Test 1: Objects on stack are preserved.\n");
  VM* vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);

  gc(vm);
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

void test3() {
  printf("Test 3: Reach nested objects.\n");
  VM* vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);
  pushPair(vm);
  pushInt(vm, 3);
  pushInt(vm, 4);
  pushPair(vm);
  pushPair(vm);

  gc(vm);
  assertLive(vm, 7);
  freeVM(vm);
}

void test4() {
  printf("Test 4: Handle cycles.\n");
  VM* vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);
  Object* a = pushPair(vm);
  pushInt(vm, 3);
  pushInt(vm, 4);
  Object* b = pushPair(vm);

  a->tail = b;
  b->tail = a;

  gc(vm);
  assertLive(vm, 4);
  freeVM(vm);
}

void perfTest() {
  printf("Performance Test.\n");
  VM* vm = newVM();

  for (int i = 0; i < 100000; i++) {
    for (int j = 0; j < 20; j++) {
      pushInt(vm, i);
    }

    for (int k = 0; k < 20; k++) {
      pop(vm);
    }
  }
  freeVM(vm);
}

int main(int argc, const char * argv[]) {
  test1();
  test2();
  test3();
  test4();
  perfTest();
  return 0;
}
