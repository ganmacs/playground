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

int N, M;
vector<int> mm[100000];
bool a[200][200] = {};

int dfs(int u, int pre) {
  int ret = 1;
  for (auto v: mm[u]) {
    if (!a[u][v]) {
      a[u][v] = true;

      if (pre != v) {
        ret *= dfs(v, u);
      }
    } else {
      ret = 0;
    }
  }
  return ret;
}

int main(int argc, char *argv[])
{
  cin >> N >> M;

  int u, v;
  for (int i = 0; i < M; i++) {
    cin >> u >> v;
    mm[u].push_back(v);
    mm[v].push_back(u);
    a[u][v] = false;
    a[v][u] = false;
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    ans += dfs(i, -1);
  }

  cout << ans << endl;
}
