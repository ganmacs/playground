#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>

void test_fd() {
  printf("%d\n", STDIN_FILENO);
  printf("%d\n", STDOUT_FILENO);
  printf("%d\n", STDERR_FILENO);

  int fd;

  fd = open("./foo",  O_CREAT | O_TRUNC, 0644);
  printf("%d in test_fd\n", fd);
  close(fd);
}

void test_read() {
  unsigned long word;
  ssize_t nr;
  int fd;
  int len = sizeof(unsigned long);
  int ret = 0;

  fd = open("./foo", O_RDONLY);
  printf("%d in test_read\n", fd);

  /* while (len != 0 && (ret = read(fd, &word, len)) != 0) { */
  /*   if (ret == -1) { */
  /*     if (errno == EINTR) */
  /*       continue; */

  /*     perror("read"); */
  /*     break; */
  /*   } */

  /*   len -= ret; */
  /*   word += ret; */
  /* } */

  close(fd);
}

int main(int argc, char *argv[])
{
  test_fd();
  test_read();
  return 0;
}
