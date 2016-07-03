#include <stdio.h>
#include <stdlib.h>

void b_search_first(int t, int ary[], int size)
{

  int l = - 1, r = size, p;

  while (l + 1 != r) {
    p = (l + r) / 2;

    if (ary[p] < t) {
      l = p;
    } else {
      r = p;
    }
  }

  if (p >= size || ary[r] != t) {
    puts("Not Found");
  } else {
    printf("Found: ary[%d]=%d\n", r, ary[r]);
  }
}

int main(int argc, char *argv[])
{
  int b[] = {0, 1, 3, 3, 3, 3, 3, 3, 4, 6, 8, 9, 11, 24, 29, 30, 35, 38, 40};
  b_search_first(10, b, 14);
  b_search_first(0, b, 14);
  b_search_first(3, b, 14);
  b_search_first(40, b, 14);
  b_search_first(24, b, 14);

  return 0;
}
