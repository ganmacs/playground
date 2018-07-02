/*
  User Thread Library
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include "thread.h"

#define DEBUG(s)	puts(s)

#ifndef TRUE
#define TRUE		1
#define FALSE		0
#endif

#define	CONTEXT_SIZE	5
#define STACK_SIZE	(4096 * 8)

typedef struct _Thread {
    struct _Thread*	next;
    int			thread_id;
    int			context[CONTEXT_SIZE];
    char*		stack_top;	/* NULL if this is main() thread */
    int			status;
    int     fd;
} Thread;

#define RUNNING		0
#define FINISH		1
#define WAITING		2

static Thread* currentThread;
static Thread* threadList;

/* in csw-i386.S */
void _ContextSwitch(int* old_context, int* new_context);
void _MakeThread(int* context, char* stack, void (*func)(int, int),
		 int arg1, int arg2);
int _TestAndSet(int* lock);

static void LinkThread(Thread* t);
static void ThreadStart(int proc, int arg);
static Thread* AllocateThread();
static void FreeThread(Thread* t);
static int isMain(Thread* t);

void main(int args, char** argv)
{
  void ThreadMain(int, char**);
  Thread *mthread = AllocateThread();
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
  child->stack_top = (char*)malloc(STACK_SIZE);
  _MakeThread(child->context, child->stack_top + STACK_SIZE, ThreadStart, (int)proc, arg);
  child->status = RUNNING;
  LinkThread(child);
  return child->thread_id;
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


Thread* searchAvailableThread() {
  Thread* t = threadList;
  for (; t != NULL; t = t->next) {
    if ((t != currentThread) && (t->status == RUNNING)) {
      break;
    }
  }

  return t;
}

/*
  ThreadYield() switches the context.
*/
void ThreadYield()
{
  fd_set readable;
  int mfd = -1;

  Thread* t = threadList;
  for (; t != NULL; t = t->next) {
    if (t->status == WAITING) {
      FD_SET(t->fd, &readable);
      if (mfd < t->fd) { mfd = t->fd; }
    }

    if ((t != currentThread) && (t->status == RUNNING)) {
      break;
    }
  }

  if (t == NULL && mfd >= 0) {
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    do {
      int afd = select(mfd, &readable, NULL, NULL, &timeout);
      Thread* tt = threadList;
      for (; tt != NULL; tt = tt->next) {
        if (tt->fd == afd) {
          tt->status = RUNNING;
        }
      }

      t = threadList;
      for (; t != NULL; t = t->next) {
        if ((t != currentThread) && (t->status == RUNNING)) {
          break;
        }
      }
    } while (t == NULL && currentThread->status != RUNNING);
  }

  if (t != NULL) {
    Thread* cur = currentThread;
    currentThread = t;
    _ContextSwitch(cur->context, t->context);
  } else if (threadList->next == NULL && threadList->status == RUNNING) {
    printf("running thread is main only\n");
    Thread *cur = currentThread;
		currentThread = threadList;
		_ContextSwitch(cur->context, threadList->context);
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
    dummy.stack_top = cur->stack_top;
    currentThread = &dummy;
    FreeThread(cur);
  }
  ThreadYield();
}

static int isMain(Thread* t) {
  return t->stack_top == NULL;
}

int ThreadRead(int fd, char* buf, int size)
{
  currentThread->status = WAITING;
  currentThread->fd = fd;
  ThreadYield();
  return read(fd, buf, size);
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
    t->stack_top = NULL;
    t->status = RUNNING;
    return t;
}

static void FreeThread(Thread* t)
{
    free(t->stack_top);
    free(t);
}
