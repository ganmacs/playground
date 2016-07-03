/* 引数が変わる */

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

void b_search_r(int t, int ary[], int l, int r)
{
  if (l > r) {
    puts("Not Found");
    return;
  }

  int p = (l + r) / 2;

  if (t > ary[p]) {
    b_search_r(t, ary, p + 1, r);
  } else if (t < ary[p]) {
    b_search_r(t, ary, l, p - 1);
  } else {
    printf("Found: ary[%d]=%d\n", p, ary[p]);
    return;
  }
}

int main(int argc, char *argv[])
{
  int a[] = {0, 1, 3, 4, 6, 8, 9, 11, 24, 29, 30, 35, 38, 40};
  b_search(10, a, 14);
  b_search(0, a, 14);
  b_search(3 , a, 14);
  b_search(40, a, 14);
  b_search(24, a, 14);

  puts("");

  b_search_r(10, a, 0, 14);
  b_search_r(0 , a, 0, 14);
  b_search_r(3 , a, 0, 14);
  b_search_r(40, a, 0, 14);
  b_search_r(24, a, 0, 14);

  return 0;
}
