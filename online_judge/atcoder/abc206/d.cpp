#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

map<int, vector<int>> M;
bool d[212345];

int ans = 0;

void dfs(int i) {
  for (auto& vi: M[i]) {
    if (d[vi]) continue;
    d[vi] = true;
    ans++;
    dfs(vi);
  }
}

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) cin >> vi;

  if (N == 1) {
    cout << 0 << endl;
    return 0;
  }

  fill(d, d + 212345, false);
  for (int i = 0; i < (N/2); i++) {
    if (V[i] == V[N - i - 1]) continue;
    M[V[i]].push_back(V[N-i-1]);
    M[V[N-i-1]].push_back(V[i]);
  }

  for (auto& vi: M) {
    auto v = vi.first;
    d[v] = true;
    dfs(v);
  }

  cout << ans << endl;

  return 0;
}
