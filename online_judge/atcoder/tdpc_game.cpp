#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

const int INF = 1e9;

bool rr[1010][1010], rr2[1010][1010];
int  mem[1010][1010], mem2[1010][1010];
int A, B, a[1010], b[1010];

int dfs(int l, int r, int n) {
  if (n % 2 == 0) {
    if (rr[l][r])  {
      return mem[l][r];
    }
  } else {
    if (rr2[l][r])  {
      return mem2[l][r];
    }
  }

  int ret = 0;
  if (l<A && r<B) {
    int r1 = dfs(l + 1, r, n + 1) + a[l];
    int r2 = dfs(l, r + 1, n + 1) + b[r];
    ret = max(r1, r2);
  } else if (l < A) {
    ret = dfs(l + 1, r, n + 1) + a[l];
  } else if (r < B) {
    ret = dfs(l, r + 1, n + 1) + b[r];
  } else {
    ret = 0;
  }

  rr[l][r] = true;
  return mem[l][r];
}

int main(int argc, char *argv[])
{
  cin >> A >> B;

  for (int i = 0; i < A; i++) cin >> a[i];
  for (int i = 0; i < B; i++) cin >> b[i];

  cout << dfs(0, 0, 0) << endl;
}
