#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

typedef struct _Thread {
  struct _Thread*	next;
  jmp_buf* context;
  int id;
} Thread;

static Thread* threadList;
static jmp_buf mainBuf;

void start(jmp_buf c, int j) {
  int x = 11;
  printf("result2 = %d:: %d\n", x, j);
  longjmp(c, 2);
}

void make_prim(jmp_buf *c, int i) {
  int _reserve[10000];
  int result = setjmp(*c);
  if (result != 0) {
    printf("this is %d!!\n", i);
    longjmp(mainBuf, 1);
  }
}

void make_prim2(jmp_buf *c, Thread* i) {
  int _reserve[10000];
  int result = setjmp(*c);
  if (result != 0) {
    printf("this is%d, %p!!\n", i->id, i);
    longjmp(mainBuf, 1);
  }
}

void create() {
  static int id = 1;
  Thread* t = (Thread*)malloc(sizeof(Thread));
  t->id = id++;
  jmp_buf* buf = (jmp_buf*)malloc(sizeof(jmp_buf));
  t->context = buf;
  make_prim(buf, t->id);

  Thread* tmp;
  tmp = threadList;
  threadList = t;
  threadList->next = tmp;
}

void create2() {
  static int id = 1;
  Thread* t = (Thread*)malloc(sizeof(Thread));
  t->id = id++;
  jmp_buf* buf = (jmp_buf*)malloc(sizeof(jmp_buf));
  t->context = buf;
  printf("%p\n", t);
  make_prim2(buf, t);

  Thread* tmp;
  tmp = threadList;
  threadList = t;
  threadList->next = tmp;
}

int main() {
  create2();
  printf("yey 1\n");
  create2();
  printf("yey 2\n");
  create2();
  printf("yey 3\n");

  Thread* t = threadList;
  printf("%d\n", t->id);

  int result = setjmp(mainBuf);

  if (result == 0) {
    printf("%p\n", t);
    longjmp(*t->context, 1);
  } else {
    t = t->next;
    if (t == NULL) return 0;
    printf("a %p\n", t);
    longjmp(*t->context, 1);
  }
}
