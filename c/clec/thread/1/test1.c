#include <stdio.h>
#include "thread.h"

void f(int i)
{
    printf("thread (i=%d) invoked.\n", i);
}

void ThreadMain()
{
    int t1, t2, t3, t4;

    t1 = ThreadCreate(f, 1);
    printf("create a new thread (i=%d) [id=%d]\n", 1, t1);
    t2 = ThreadCreate(f, 2);
    printf("create a new thread (i=%d) [id=%d]\n", 2, t2);
    t3 = ThreadCreate(f, 3);
    printf("create a new thread (i=%d) [id=%d]\n", 4, t3);
    ThreadYield();
    t4 = ThreadCreate(f, 4);
    printf("create a new thread (i=%d) [id=%d]\n", 4, t4);

    printf("main thread invoked.\n");
}
