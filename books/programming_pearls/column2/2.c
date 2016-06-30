/* ２分探索で常に大きい方を探しに行く */

#include <stdio.h>
#include <stdlib.h>

#define N 10

void mbsearch(int l, int r, int lst[], int size)
{
  int p = (l + r) / 2;
  int l_lst[p + 1], r_lst[p + 1];
  int l_c = 0, r_c = 0;
  int flg = 0;

  /* for (int i = 0; i < size; i++) { */
  /*   printf("%d\n", lst[i]); */
  /* } */

  for (int i = 0; i < size; i++) {
    if (p <= lst[i]) {
      if (p == lst[i]) flg++;
      if (r_c >= p + 1) continue;
      r_lst[r_c] = lst[i];
      r_c++;
    } else {
      if (l_c >= p + 1) continue;
      l_lst[l_c] = lst[i];
      l_c++;
    }
  }

  if (flg > 1) {
    printf("%d\n", p);
    return;
  }

  if (l_c >= p + 1) {
    mbsearch(l, p, l_lst, l_c);
  } else if (r_c >= p + 1) {
    mbsearch(p, r, r_lst, r_c);
  } else {
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  int seed[] = { 1, 4, 5, 1, 2, 6, 1, 7, 8, 9, 3, 10, 0 };
  mbsearch(0, N, seed, N + 2);
  return 0;
}
