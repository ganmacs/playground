/*
  User Thread Library
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/time.h>
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
  sigset_t  signal_mask;
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

#define FALSE 0
#define TRUE 1

static int mutex = 0;
static int kernelLock;
static int needContextSwitch;

void PreemptiveScheduler(int x) {
  printf("called preemptivescheduler kernelLock=%d,  needContextSwitch=%d\n", kernelLock, needContextSwitch);
  if (kernelLock == FALSE) {
    ThreadYield();
  } else {
    needContextSwitch = TRUE;
  }
}

void setTimer() {
  puts("set Timer");
  struct itimerval s, t;
  t.it_interval.tv_sec = t.it_value.tv_sec = 0;
  t.it_interval.tv_usec = t.it_value.tv_usec = 100000;
  signal(SIGALRM, PreemptiveScheduler);
  setitimer(ITIMER_REAL, &t, &s);
}

void critical()
{
  int value;
  do {
    value = _TestAndSet(&mutex);
  } while (value != 0);

  mutex = 0;
}

void main(int args, char** argv)
{
  void ThreadMain(int, char**);
  Thread *mthread = AllocateThread();
  currentThread = mthread;
  threadList = mthread;

  setTimer();
  ThreadMain(args, argv);
  ThreadExit();
  free(mthread);
}

int ThreadCreate(ThreadProc proc, int arg)
{
  kernelLock = TRUE;
  static int id = 1;
  Thread* child = (Thread*)malloc(sizeof(Thread));
  child->thread_id = id++;
  child->stack_top = (char*)malloc(STACK_SIZE);
  sigprocmask(SIG_SETMASK, NULL, &child->signal_mask);
  _MakeThread(child->context, child->stack_top + STACK_SIZE, ThreadStart, (int)proc, arg);
  child->status = RUNNING;
  LinkThread(child);

  kernelLock = FALSE;
  if (needContextSwitch == TRUE) {
    ThreadYield();
  }
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

/*
  ThreadYield() switches the context.
*/
void ThreadYield()
{
  puts("thread yield");
  kernelLock = TRUE;
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
    sigprocmask(SIG_SETMASK, &t->signal_mask, &cur->signal_mask);
    printf("context switch %d -> %d\n", cur->thread_id, t->thread_id);
    kernelLock = FALSE;
    _ContextSwitch(cur->context, t->context);
  } else if (threadList->next == NULL && threadList->status == RUNNING) {
    printf("running thread is main only\n");
    Thread *cur = currentThread;
		currentThread = threadList;
    sigprocmask(SIG_SETMASK, &threadList->signal_mask, &cur->signal_mask);
    kernelLock = FALSE;
		_ContextSwitch(cur->context, threadList->context);
  }

  needContextSwitch = FALSE;
}

/*
  ThreadExit() finishes the current thread.
  If this thread is main(), this function waits until all tasks finish,
  then normally returns.
*/
void ThreadExit()
{
  kernelLock = TRUE;
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
  kernelLock = FALSE;

  if (needContextSwitch == TRUE) {
    ThreadYield();
  }
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
