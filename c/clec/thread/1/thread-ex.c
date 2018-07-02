/*
  User Thread Library
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <setjmp.h>
#include "thread.h"

#define DEBUG(s)	puts(s)

#ifndef TRUE
#define TRUE		1
#define FALSE		0
#endif

#define STACK_SIZE	(4096 * 8)

typedef struct _Thread {
  struct _Thread*	next;
  int      thread_id;
  jmp_buf* context;
  int      status;
  int      main;
} Thread;

#define RUNNING		0
#define FINISH		1

static Thread* currentThread;
static Thread* threadList;

int MakeThread(jmp_buf* context, void (*func)(int, int), int arg1, int arg2) {
  int result = setjmp(*context);
  if (result != 0) {
    func(arg1, arg2);
  }

  return result;
}

void ContextSwitch(Thread* t) {
  longjmp(*t->context, 1);
}

static void LinkThread(Thread* t);
static void ThreadStart(int proc, int arg);
static Thread* AllocateThread();
static void FreeThread(Thread* t);
static int isMain(Thread* t);

int main(int args, char** argv)
{
  void ThreadMain(int, char**);
  Thread *mthread = AllocateThread();
  mthread->main = 1;
  currentThread = mthread;
  threadList = mthread;

  ThreadMain(args, argv);
  ThreadExit();
  free(mthread);
}

int ThreadCreate(ThreadProc proc, int arg)
{
  static int id = 1;
  Thread* child = (Thread*)malloc(sizeof(Thread));
  child->thread_id = id++;
  child->status = RUNNING;
  child->main = 0;
  LinkThread(child);

  jmp_buf* buf = (jmp_buf*)malloc(sizeof(jmp_buf));
  child->context = buf;

  if (MakeThread(child->context, ThreadStart, (int)proc, arg) == 0) {
    return child->thread_id;
  } else {
    return child->thread_id;
  }
}

static void LinkThread(Thread* t)
{
  Thread* tmp;

  tmp = threadList;
  threadList = t;
  threadList->next = tmp;
}

/*
  ThreadStart() is a procedure that threads first invoke.
*/
static void ThreadStart(int proc, int arg)
{
  ThreadProc ptr = (ThreadProc)proc;
  (*ptr)(arg);
  ThreadExit();
}

/*
  ThreadYield() switches the context.
*/
void ThreadYield()
{
  Thread* t = threadList;
  for (; t != NULL; t = t->next) {
    if ((t != currentThread) && (t->status == RUNNING)) {
      break;
    }
  }

  if (t != NULL) {
    Thread* cur = currentThread;
    currentThread = t;
    ContextSwitch(cur);
  } else if (t == NULL && isMain(t)) {
    /*  threadList has only main thread whose status is FINISH */
    return;
  }
}

/*
  ThreadExit() finishes the current thread.
  If this thread is main(), this function waits until all tasks finish,
  then normally returns.
*/
void ThreadExit()
{
  static Thread dummy;
  Thread* cur = currentThread;
  if (isMain(cur)) {
    printf("main thread finished.\n");
    cur->status = FINISH;
  } else {
    printf("thread id(#%d) finished.\n", cur->thread_id);
    Thread* t = threadList;
    /* cur is head */
    if (t == cur) {
      threadList = threadList->next;
    } else {
      for (; t != NULL; t = t->next) {
        if (t->next == cur) {
          t->next = t->next->next;
        }
      }
    }

    dummy.status = FINISH;
    currentThread = &dummy;
    FreeThread(cur);
  }
  ThreadYield();
}

static int isMain(Thread* t) {
  return t->main == 1;
}

static Thread* AllocateThread()
{
  static int n = 1;
  Thread* t;

  if ((t = (Thread*)malloc(sizeof(Thread))) == NULL) {
    DEBUG("*** error: fail to allocate a thread");
    exit(1);	/* error: no memory */
  }

  t->next = NULL;
  t->thread_id = n++;
  t->status = RUNNING;
  return t;
}

static void FreeThread(Thread* t)
{
  free(t);
}
