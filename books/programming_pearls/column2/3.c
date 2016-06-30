/* Problem B */
/* roteta string by n */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate1(char source[], int size, int n)
{
  char tgt[size];
  stpcpy(tgt, source);

  int mem[size];
  for (int i = 0; i < size; i++) mem[i] = 0;

  int resume = 1, prev;

  while (resume) {
    for (int i = 0; i < size; i++) {
      if (!mem[i]) {
        prev = i;
        mem[i] = 1;
        break;
      }
    }

    int j = prev + n;
    char tmp = tgt[prev];

    while (j != 0) {
      if (mem[j]) break;
      tgt[prev] = tgt[j];
      mem[prev] = 1;
      prev = j;
      j = (j + n) % size;
    }
    tgt[prev] = tmp;

    resume = 0;
    for (int i = 0; i < size; i++) {
      if (!mem[i]) {
        resume = 1;
        break;
      }
    }
  }

  printf("%s\n", tgt);
}

void reverse(char str[], int l, int r)
{
  int size = r - l;
  printf("%d\n",  l + size/2);
  for (int i = l; i <= l + size/2 ; i++) {
    char t = str[i];
    str[i] = str[r - (i - l)];
    str[r - (i - l)] = t;
  }
}

void rotate2(char source[], int size, int n)
{
  reverse(source, 0, n);
  reverse(source, n + 1, size - 1);
  reverse(source, 0, size - 1);

  printf("%s\n", source);
}

int main(int argc, char *argv[])
{
  rotate1("abcde", 5, 3);       /* defabc */
  rotate1("abcdef", 6, 3);       /* defabc */

  rotate1("abcde", 5, 3);       /* defabc */
  rotate1("abcdef", 6, 3);       /* defabc */

  return 0;
}
