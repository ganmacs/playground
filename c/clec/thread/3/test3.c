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
    printf("%d-loop %d\n", i, j);
  }

  printf("thread (i=%d) finished.\n", i);
}

void ThreadMain()
{
  int t1, t2;

  t1 = ThreadCreate(f, 1);
  printf("create a new thread (i=%d) [id=%d]\n", 1, t1);
  t2 = ThreadCreate(f, 2);
  printf("create a new thread (i=%d) [id=%d]\n", 2, t2);
  xsleep();
  printf("main thread finished.\n");
}
