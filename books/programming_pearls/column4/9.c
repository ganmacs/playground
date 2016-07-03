/*
  1.
  input: 長さをnのa, b, cの配列
  output: 0 <= k < nを満たすkに於いて常に a[k] = b[k] + c[k]を満たすaの配列
  ループ普遍条件: a[i]には常に b[i] + c[i]が入る、またiは0 <= i <= n

  2.
  input: 長さをn配列x(空はダメ)
  output: 配列xの要素の中で最大の数 max
  ループ普遍条件: maxにはiまでの最大の数が代入されている

  3.
  input: 任意の長さの配列xとけんさくする数字t
  output: 初めてtが現れる配列xの添字。なければ-1
  ループ普遍条件: x[i] != tであること。 i は 0 <= i <= nであること

  4.
  下のプログラム

*/

#include <stdio.h>
#include <stdlib.h>

int exp_r(int x, int n)
{

  if (n == 0) return 1;
  if (n == 1) return x;
  else if (n % 2 == 1) return x * exp_r(x, n - 1);
  else {
    int v = exp_r(x, n >> 1);
    return  v * v;
  }
}

int exp_l(int x, int n)
{
  if (n == 0) return 1;

  int v = x;
  int i = 1;

  while (n != 1) {
    if (n % 2 == 1) {
      v++;
      n--;
    } else {
      v <<= 1;

    }
  }
}

int main(int argc, char *argv[])
{
  printf("%d\n", exp_r(2, 1));
  printf("%d\n", exp_l(2, 10));

  return 0;
}
