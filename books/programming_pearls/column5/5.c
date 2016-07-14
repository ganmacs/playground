#include <stdio.h>
#include <stdlib.h>

int mbsearch(int lst[], int size, int target)
{
  int r = size - 1, l = 0;
  int p;
  while (l < r) {
    p = (r + l) / 2;

    if (lst[p] < target) {
      l = p + 1;
    } else if (lst[p] > target) {
      r = p - 1;
    } else if (lst[p] == target) {
      printf("lst[%d] = %d\n", p, lst[p]);
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int a[10], b[10];
  for (int i = 0; i < 10; i++) {
    a[i] = i;
    b[i] = i;
  }

  int t = b[5];
  b[5] = b[7];
  b[7] = t;

  puts("lst a");
  printf("%d\n", mbsearch(a, 10, 8));

  puts("lst b");
  mbsearch(b, 10, 8);
  return 0;
}
