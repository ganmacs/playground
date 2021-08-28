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

map<int, vector<int>> M;
map<int, long long> S;
map<int, long long> A;

void dfs(int i, int prev, long long s)
{
  A[i] += (s + S[i]);
  for (auto& ni: M[i]) {
    if (prev == ni) continue;
    dfs(ni, i, s + S[i]);
  }
}

int main()
{
  int N, Q, a, b;
  long long x;
  cin >> N >> Q;
  for (int i = 0; i < (N-1); i++) {
    cin >> a >> b;
    M[a].push_back(b);
    M[b].push_back(a);
  }

  for (int i = 0; i < Q; i++) {
    cin >> a >> x;
    S[a] += x;
  }

  dfs(1, -1, 0);

  for (int i = 0; i < N; i++) {
    printf("%lld ", A[i + 1]);
  }
  puts("");

  return 0;
}
