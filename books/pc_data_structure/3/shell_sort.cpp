#include <cstdio>
#include <iostream>
using namespace std;
static const int M = 1000000;

void pp(int v[], int size)
{
  for (int i = 0; i < size; i++) {
    cout << v[i] << endl;
  }
}

void print_int_ary(int v[], int size)
{
  for (int i = 0; i < size-1; i++) {
    cout << v[i]  << ' ';
  }
  cout << v[size-1] << endl;
}

int insert(int v[], int n, int g)
{
  int j, t, cnt = 0;

  for (int i = g; i < n; i++) {
    j = i - g;
    t = v[i];
    while (j >= 0 && v[j] > t) {
      v[j + g] = v[j];
      j -= g;
      cnt++;
    }
    v[j + g] = t;
  }

  return cnt;
}

int main(int argc, char *argv[])
{
  int n, cnt = 0, m = 13, k = 0;
  int v[M], retg[m];
  int g[] = { 8192, 4096, 2048, 1024, 512, 256, 64, 32, 16, 8, 4, 2, 1 };

  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i];


  for (int i = 0; i < m; i++) {
    if (g[i] <= n) {
      retg[k++] = g[i];
      cnt += insert(v, n, g[i]);
    }
  }

  cout << k <<endl;
  print_int_ary(retg, k);
  cout << cnt <<endl;
  pp(v, n);

  return 0;
}
