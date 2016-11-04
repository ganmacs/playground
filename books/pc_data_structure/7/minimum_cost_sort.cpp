#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

#define N 1000
int const WMAX = 10000;
int n;

int A[N], B[N], T[WMAX + 1];
bool F[WMAX + 1];

int solve(int m)
{
  int i, an, c, mm, ans = 0, S, v;

  sort(B, B + n);
  for (i = 0; i < n; i++) T[B[i]] = i;

  for (i = 0; i < n; i++) {
    if (F[i]) continue;
    c = i;
    an = 0;
    S = 0;
    mm = WMAX;

    while (1) {
      F[c] = true;
      an++;
      v = A[c];
      S += v;
      mm = min(v, mm);
      c = T[v];                   // next C
      if (F[c]) break;
    }

    ans += min(S + (an - 2) * mm , mm + S + (an + 1) * m);
  }

  return ans;
}

int main(int argc, char *argv[])
{
  int i, m = WMAX;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &A[i]);
    B[i] = A[i];
    F[i] = false;
    m = min(m, A[i]);
  }

  cout << solve(m) << endl;
  return 0;
}
