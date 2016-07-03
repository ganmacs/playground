#include <stdio.h>
#include <stdlib.h>

void b_search(int t, int ary[], int size)
{
  int l = 0, r = size - 1, p;
  int c = 0;

  while (l <= r) {
    c++;
    p = (l + r) / 2;
    if (t > ary[p])      l = p + 1;
    else if (t < ary[p]) r = p - 1;
    else {
      printf("c=%d\n", c);
      printf("Found: ary[%d]=%d\n", p, ary[p]);
      return;
    }
  }
  printf("c=%d\n", c);
  puts("Not Found");
}

int main(int argc, char *argv[])
{
  int a[] = {0, 1, 3, 4, 6, 8, 9, 11, 24, 29, 30, 35, 38, 40};
  b_search(10, a, 14);          /* 見つからない時が最悪だから 4  log(14) */
  b_search(0, a, 14);
  b_search(3 , a, 14);
  b_search(40, a, 14);
  b_search(24, a, 14);
  return 0;
}
