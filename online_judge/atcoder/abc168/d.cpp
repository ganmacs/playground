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

bool visited[112345];
int from[112345];

int main()
{
  map<int, vector<int>> V;
  int N, M, a, b;
  cin >> N >> M;
  priority_queue<pair<int, pair<int, int>>> Q;

  fill(visited, visited + N, false);
  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    a--, b--;
    V[a].push_back(b);
    V[b].push_back(a);
  }

  Q.push({0, {0, 0}});

  while (!Q.empty()) {
    auto v = Q.top();
    int w = v.first;
    int tgt = v.second.first;
    int src = v.second.second;
    Q.pop();
    if (visited[tgt]) continue;

    visited[tgt] = true;
    from[tgt] = src;

    for (auto& vi: V[tgt]) {
      if (!visited[vi]) Q.push({ w - 1, { vi, tgt }});
    }
  }

  puts("Yes");
  for (int i = 1; i < N; i++) {
    printf("%d\n", from[i] + 1);
  }

  return 0;
}
