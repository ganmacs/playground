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

int  mem[1010][1010];
int A, B, a[1010], b[1010];

int dfs(int l, int r, int n) {
  if (A == l && B == r) return 0;
  if (mem[l][r] != -1) return mem[l][r];

  int v;
  if (n == 0) {
    v = -INF;
    if (l < A) v = max(dfs(l + 1, r, 1) + a[l], v);
    if (r < B) v = max(dfs(l, r + 1, 1) + b[r], v);
  } else {
    v = INF;
    if (l < A) v = min(dfs(l + 1, r, 0), v);
    if (r < B) v = min(dfs(l, r + 1, 0), v);
  }

  mem[l][r] = v;
  return v;
}

int main(int argc, char *argv[])
{
  cin >> A >> B;

  for (int i = 0; i < A; i++) cin >> a[i];
  for (int i = 0; i < B; i++) cin >> b[i];

  for (int i = 0; i <= A; i++) {
    for (int j = 0; j <= B; j++) {
      mem[i][j] = -1;
    }
  }

  cout << dfs(0, 0, 0) << endl;
}
