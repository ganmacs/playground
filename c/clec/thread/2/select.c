#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

void readability_check(int fd1, int fd2)
{
  fd_set readable;
  struct timeval timeout;
  int maxfd;

  FD_ZERO(&readable);
  FD_SET(fd1, &readable);
  FD_SET(fd2, &readable);

  if (fd1 > fd2) {
    maxfd = fd1 + 1;
  } else {
    maxfd = fd2 + 1;
  }

  timeout.tv_sec = 1;                 // タイムアウトは 0 秒
  timeout.tv_usec = 0;

  if (select(maxfd, &readable, NULL, NULL, &timeout) < 0) {
    perror("select");
    exit(1);
  }
  if (FD_ISSET(fd1, &readable)) {
    printf("fd1 set\n");
  } else if (FD_ISSET(fd2, &readable)) {
    printf("fd2 set\n");
  } else  {
    printf("timeout\n");
  }
}

int main(int argc, char *argv[])
{
  readability_check(0, 1);
  return 0;
}
