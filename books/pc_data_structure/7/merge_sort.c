#include <stdio.h>
#include <stdlib.h>

#define M 500000
#define SEN 2000000000;
int v[M], n, L[M/2 + 2], R[M/2 + 2];
int count;

void pp()
{
  int i = 0;
  for (; i < n; i++) {
    if (i != 0)
      printf(" ");
    printf("%d", v[i]);
  }
  puts("");
}

void merge(int l, int r, int m)
{
  int i;
  int ln = m - l;
  int rn = r - m;

  for (i = 0; i <= ln; i++) L[i] = v[l + i];
  L[ln + 1] = SEN;

  for (i = 1; i <= rn; i++) R[i - 1] = v[m + i];
  R[rn] = SEN;

  int rk = 0, lk = 0;
  for (i = l; i <= r; i++) {
    count++;
    if (L[lk] < R[rk]) {
      v[i] = L[lk++];
    } else {
      v[i] = R[rk++];
    }
  }
}

void merge_sort(int l, int r)
{
  if (l < r) {
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, r, mid);
  }
}

int main(int argc, char *argv[])
{
  count = 0;
  scanf("%d", &n);
  int i = 0;
  for (; i < n; i++) scanf("%d", &v[i]);
  merge_sort(0, n - 1);
  pp();
  printf("%d\n", count);
  return 0;
}
