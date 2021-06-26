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
map<int, vector<int>> V;
map<int, long long> M;
long long d[212345];

void dfs(int i, long long aa, int p)
{
  d[i] += aa;
  for (auto& vi: V[i]) {
    if (p == vi) continue;
    dfs(vi, aa + M[vi], i);
  }
}

int main()
{
  int N, Q, aa, bb;
  cin >> N >> Q;

  for (int i = 0; i < (N-1); i++) {
    cin >> aa >> bb;
    V[aa].push_back(bb);
    V[bb].push_back(aa);
  }
  fill(d, d + N + 2, 0);

  for (int i = 0; i < Q; i++) {
    cin >> aa >> bb;
    M[aa] += bb;
  }
  dfs(1, M[1], -1);

  for (int i = 1; i <= N; i++) {
    cout << d[i] << " ";
  }

  puts("");
  return 0;
}
