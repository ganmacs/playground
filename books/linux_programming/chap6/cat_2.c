#include <stdio.h>
#include <stdlib.h>

static void do_cat();

int
main(int argc, char *argv[])
{
  if (argc == 1) {
    do_cat();
  }

  exit(0);
}

static void
do_cat()
{
  int c;
  int count = 1;
  int in = 0;

  while ((c = fgetc(stdin)) != EOF) {
    in = 1;

    if (c == '\n') {
      count++;
      in = 0;
    }
  }

  if (!in) count--;
  printf("%d\n", count);
}
