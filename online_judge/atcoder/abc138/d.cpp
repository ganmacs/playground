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
#include <numeric>

using namespace std;

int N, Q, a, b;
int V[212345];
map<int, vector<int>> M;

void dfs(int t, int pre) {
  for (auto& vi: M[t]) {
    if (vi != pre) {            // do not go back
      V[vi] += V[t];
      dfs(vi, t);
    }
  }
}

int main()
{
  cin >> N >> Q;
  for (int i = 0; i < (N-1); i++) {
    cin >> a >> b;
    a--; b--;
    M[a].push_back(b);
    M[b].push_back(a);
  }
  fill(V, V + N, 0);

  for (int i = 0; i < Q; i++) {
    cin >> a >> b;
    V[a-1] += b;
  }

  dfs(0, -1);
  for (int i = 0; i < N; i++) {
    cout << V[i] << " ";
  }
  puts("");

  return 0;
}
