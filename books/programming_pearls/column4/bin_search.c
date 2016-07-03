#include <stdio.h>
#include <stdlib.h>

void b_search(int t, int ary[], int size)
{
  int l = 0, r = size - 1, p;

  while (l <= r) {
    p = (l + r) / 2;
    if (t > ary[p])      l = p + 1;
    else if (t < ary[p]) r = p - 1;
    else {
      printf("Found: ary[%d]=%d\n", p, ary[p]);
      return;
    }
  }
  puts("Not Found");
}

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
  int a[] = {0, 1, 3, 4, 6, 8, 9, 11, 24, 29, 30, 35, 38, 40};
  b_search(10, a, 14);
  b_search(0, a, 14);
  b_search(40, a, 14);
  b_search(24, a, 14);

  puts("");

  int b[] = {0, 1, 3, 3, 3, 3, 3, 3, 4, 6, 8, 9, 11, 24, 29, 30, 35, 38, 40};
  b_search_first(10, b, 14);
  b_search_first(0, b, 14);
  b_search_first(3, b, 14);
  b_search_first(40, b, 14);
  b_search_first(24, b, 14);

  return 0;
}
