#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N, M, K, a, b;
  cin >> N >> M >> K;
  map<int, set<int>> A;

  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    a--;b--;
    A[a].insert(b);
    A[b].insert(a);
  }

  vector<int> root(N, -1);
  vector<int> aa(N, 0);
  for (int i = 0; i < N; i++) {
    if (root[i] != -1) continue;

    queue<int> que;
    vector<int> vv;
    que.push(i);
    while (que.size()) {
      int nv = que.front();que.pop();
      if (root[nv] != -1) continue;
      root[nv] = i;
      vv.push_back(nv);

      for (auto& vi: A[nv]) {
        que.push(vi);
      }
    }

    for (auto& vi: vv) {
      aa[vi] = vv.size()-1;
    }
  }

  for (int i = 0; i < K; i++) {
    cin >> a >> b;
    a--;b--;

    if (root[a] == root[b]) {
      A[a].insert(b);
      A[b].insert(a);
    }
  }

  for (int i = 0; i < N; i++) {
    printf("%d ", aa[i] - (int)A[i].size());
    // printf("%d ", root[i]);
  }
  puts("");

  return 0;
}
