#include <stdio.h>
#include "thread.h"

void xsleep()
{
  int j = 100000000;
  while(j-- > 0)
    ;
}

void f(int i)
{
  int j;

  for (j = 0; j < 5; ++j) {
    xsleep();
    printf("loop %d\n", j);
  }

  printf("thread (i=%d) finished.\n", i);
}

void g(int i)
{
  char buf[32];
  int s;

  printf("<press return>\n");
  s = ThreadRead(0, buf, sizeof(buf));
  printf("<%d bytes were read>\n", s);
  printf("thread (i=%d) finished.\n", i);
}

void ThreadMain()
{
  int t1, t2;

  t1 = ThreadCreate(f, 1);
  printf("create a new thread (i=%d) [id=%d]\n", 1, t1);
  ThreadYield();
  t2 = ThreadCreate(g, 2);
  printf("create a new thread (i=%d) [id=%d]\n", 2, t2);
  printf("main thread finished.\n");
}
