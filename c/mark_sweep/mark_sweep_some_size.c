#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1024
#define STACK_SIZE 1024

/* typedef enum { */
/*   OBJ_INT, */
/*   OBJ_PAIR */
/* } ObjectType; */

typedef struct {
  int size;
  void* fileds;

  union {
    int value;

    struct {
      struct sObject* head;
      struct sObject* tail;
    };
  };
} Object;

typedef struct {
  Object* stack[STACK_SIZE];
  int stackSize;

  void* heap;
  void* next;
} VM;

typedef struct {
  void* moveTo;
  ObjectType type;
  int value;
} IntObject;
#define I_OBJ_SIZE sizeof(IntObject)

typedef struct {
  void* moveTo;
  ObjectType type;
  struct IntObject* head;
  struct IntObject* tail;
} PairObject;
#define P_OBJ_SIZE sizeof(PairObject)

/* void assertLive(VM* vm, long expectedCount) { */
/*   /\* long actualCount = (vm->next - vm->heap) / sizeof(Object); *\/ */
/*   /\* if (actualCount == expectedCount) { *\/ */
/*   /\*   printf("PASS: Expected and found %ld live objects.\n", expectedCount); *\/ */
/*   /\* } else { *\/ */
/*   /\*   printf("Expected heap to contain %ld objects, but had %ld.\n", *\/ */
/*   /\*          expectedCount, actualCount); *\/ */
/*   /\*   exit(1); *\/ */
/*   /\* } *\/ */
/* } */

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  vm->heap = malloc(STACK_SIZE);
  vm->next = vm->heap;

  return vm;
}

void mark() {

}

void markAll(VM* vm)
{
  for (int i = 0; i < vm->stackSize; i++) {
    mark(vm->stack[i]);
  }
}

void gc(VM* vm)
{
  markAll();

}

IntObject* newIntObject(VM* vm) {
  if (vm->next + I_OBJ_SIZE > vm->heap + HEAP_SIZE) {
    gc(vm);
    if (vm->next + I_OBJ_SIZE > vm->heap + HEAP_SIZE) {
      perror("Out of memory");
      exit(1);
    }
  }

  IntObject* io = (IntObject*)vm->next;
  vm->next += I_OBJ_SIZE;

  io->type = OBJ_INT;
  io->moveTo = NULL;

  return io;
}

PairObject* newPairObject(VM* vm) {
  if (vm->next + P_OBJ_SIZE > vm->heap + HEAP_SIZE) {
    gc(vm);
    if (vm->next + P_OBJ_SIZE > vm->heap + HEAP_SIZE) {
      perror("Out of memory");
      exit(1);
    }
  }

  PairObject* io = (PairObject*)vm->next;
  vm->next += P_OBJ_SIZE;

  io->type = OBJ_PAIR;
  io->moveTo = NULL;

  return io;
}

void pushInt(VM* vm, int v)
{
  IntObject* intObj = newIntObject(vm);
  intObj->value = v;

  if (vm->stackSize == STACK_SIZE) {
    perror("Stack overflow");
    exit(1);
  }
  vm->stack[vm->stackSize++] = intObj;
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
  /* assertLive(vm, 2); */
  freeVM(vm);
}

int main(int argc, char *argv[])
{
  test1();
  return 0;
}
