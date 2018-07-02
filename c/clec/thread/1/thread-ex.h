#ifndef _thread_h
#define _thread_h

typedef void (*ThreadProc)(int);

int ThreadCreate(ThreadProc proc, int arg);
void ThreadYield();
void ThreadExit();
int ThreadRead(int fd, char* buf, int size);

#endif
