/* Problem A */
/* search number by binary search */

#include <stdio.h>
#include <stdlib.h>

#define N 10

void mbsearch(int l_b, int r_b, int lst[], int size)
{
  int l[size], r[size];
  int l_i = 0, r_i = 0, ret = 1;
  int t = (l_b + r_b) / 2;
  int size_l = t;
  int size_r = (l_b + r_b) - size_l;

  for (int i = 0; i < size; i++) {
    if (lst[i] == t) {
      r[r_i] = lst[i];
      r_i++;
      ret = 0;                  /* found */
    } else if (lst[i] > t) {
      r[r_i] = lst[i];
      r_i++;
    } else {
      l[l_i] = lst[i];
      l_i++;
    }
  }

  if (ret) {
    printf("Answer is %d\n", t);
    return;
  }

  if (size_r > r_i) {
    mbsearch(t, r_b, r, size / 2 + 1);
  } else if (size_l > l_i) {
    mbsearch(l_b, t, l, size / 2);
  } else {
    puts("Invalid");
    return;
  }
}

int main(int argc, char *argv[])
{
  int seed[] = {2, 8, 7, 9, 6, 0, 1, 5, 4, 10};
  mbsearch(0, N + 1, seed, N);
  return 0;
}
