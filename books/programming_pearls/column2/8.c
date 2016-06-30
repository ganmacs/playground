/* O(nlog(n)) ...  ソートして小さい方からkことる */
/* O(n^k)     ... 配列をすべて回して常に一番小さいものを取るこれをk回繰り返す */
/* O(kn)      ... k個の配列を作って 配列すべてを見ていき小さいkこを取る */
/* O(nlog(k))      ... k個の配列を作って 配列すべてを見ていき小さいkこを取る(挿入する場所を２分探索する) */

#include<stdio.h>
#include<stdlib.h>


void
insert(int *a, int size, int n, int v)
{
  if (n >= size) return;

  a[size - 1] = v;
  for (int i = size - 1; i > n; i--) {
    int tmp = a[i - 1];
    a[i - 1] = a[i];
    a[i] = tmp;
  }
}

int
comp_func (const void *c1, const void *c2)
{
  int i1 = *(int *)c1;
  int i2 = *(int *)c2;
  return i1 - i2;
}


void
n_logn(int ary[], int ary_size, int t, int k)
{
  qsort(ary, ary_size, sizeof(int), comp_func);
  int ret = 0;

  for (int i = 0; i < k; i++) {
    ret += ary[i];
  }

  if (ret <= t) {
    puts("最高");
  } else {
    puts("最悪");
  }
}

void
n_k(int ary[], int ary_size, int t, int k)
{
  int ret = 0;

  for (int i = 0; i < k; i++) {
    for (int j = i + 1; j < ary_size; j++) {
      if (ary[i] > ary[j]) {
        int tmp = ary[i];
        ary[i] = ary[j];
        ary[j] = tmp;
      }
    }
  }

  for (int i = 0; i < k; i++) {
    ret += ary[i];
  }

  if (ret <= t) {
    puts("最高");
  } else {
    puts("最悪");
  }
}

void
kn(int ary[], int ary_size, int t, int k)
{
  int ret = 0;
  int r[k];

  for (int i = 0; i < k; i++) {
    r[i] = 1000000;             /* INT MAX */
  }

  for (int i = 0; i < ary_size; i++) {
    int j = 0;
    while (r[j] < ary[i] && j < k) j++;
    if (j == k) continue;
    insert(r, k, j, ary[i]);
  }

  for (int i = 0; i < k; i++) {
    ret += r[i];
  }

  if (ret <= t) {
    puts("最高");
  } else {
    puts("最悪");
  }
}

void
nlogk(int ary[], int ary_size, int t, int k)
{
  int ret = 0;
  int rr[k];

  for (int i = 0; i < k; i++) {
    rr[i] = 1000000;             /* INT MAX */
  }

  for (int i = 0; i < ary_size; i++) {
    int l = 0;
    int r = k;
    int p = (l + r) / 2;
    int prev = - 1;

    while ((p >= 0 && p < k)) {
      if (ary[i] <= rr[p]) {
        r = p;
      } else if(ary[i] > rr[p]){
        l = p;
      }
      prev = p;
      p = (l + r) / 2;
      if (p == prev) break;
    }


    if (p == 0 && (rr[0] < ary[i]) ) p = 1;
    if (p == k && (rr[p] > ary[i]) ) continue;

    insert(rr, k, p, ary[i]);
  }

  for (int i = 0; i < k; i++) {
    ret += rr[i];
  }

  if (ret <= t) {
    puts("最高");
  } else {
    puts("最悪");
  }
}

int main(int argc, char *argv[])
{
  int ary0[]  = {9, 1, 8, 7, 6, 5, 4, 3, 2, 1};
  int ary2[] = {9, 1, 8, 7, 6, 5, 4, 3, 2, 1};
  int ary3[] = {9, 1, 8, 7, 6, 5, 4, 3, 2, 1};
  int ary4[] = {9, 1, 8, 7, 6, 5, 4, 3, 2, 1};

  n_logn(ary0, 10, 4, 3);
  n_k(ary2, 10, 4, 3);
  kn(ary3, 10, 4, 3);
  nlogk(ary3, 10, 4, 3);

  return 0;
}
