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

map<int, vector<int>>  V;
int M[212345];

void dfs(int i, int prev, long s) {
  M[i] += s;

  for (auto& vi: V[i]) {
    if (prev != vi) {
      dfs(vi, i,  M[i]);
    }
  }
}

int main()
{
  int N, Q, a, b;;
  cin >> N >> Q;

  for (int i = 0; i < (N-1); i++) {
    cin >> a >> b;
    a--;b--;

    V[a].push_back(b);
    V[b].push_back(a);
  }

  fill(M, M + Q, 0);
  for (int i = 0; i < Q; i++) {
    cin >> a >> b;
    M[a-1] += b;
  }

  dfs(0, -1, 0);

  for (int i = 0; i < N; i++) {
    cout << M[i] << " ";
  }
  puts("");
  return 0;
}
