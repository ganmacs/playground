#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE *f);

int
main(int argc, char *argv[])
{
  int i;

  if (argc == 1) {
    do_cat(stdin);
  } else {
    FILE *f;

    for (i = 1; i < argc; i++) {
      f = fopen(argv[i], "r");

      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_cat(f);
      fclose(f);
    }
  }

  exit(0);
}

static void
do_cat(FILE *f)
{
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\t') {
      if (fputs("\\t", stdout) == EOF) exit(1);
    } else if (c == '\n'){
      if (fputs("$\n", stdout) == EOF) exit(1);
    } else {
      if (putchar(c) < 0) exit(1);
    }
  }
}
