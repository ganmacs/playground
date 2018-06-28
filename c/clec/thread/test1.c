#include <stdio.h>
#include "thread.h"

void f(int i)
{
    printf("thread (i=%d) invoked.\n", i);
}

void ThreadMain()
{
    int t1, t2;

    t1 = ThreadCreate(f, 1);
    printf("create a new thread (i=%d) [id=%d]\n", 1, t1);
    t2 = ThreadCreate(f, 2);
    printf("create a new thread (i=%d) [id=%d]\n", 2, t2);
    printf("main thread invoked.\n");
    ThreadYield();
}
