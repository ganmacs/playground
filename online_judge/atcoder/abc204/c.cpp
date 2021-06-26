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

int main()
{
  int N, M, a, b;
  map<int, vector<int >> V;
  cin >> N >> M;

  unsigned long long ans = 0;

  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    a--;b--;
    V[a].push_back(b);
  }

  for (int i = 0; i < N; i++) {
    queue<int> q;
    vector<bool> visited(N, false);
    q.push(i);

    while (!q.empty()) {
      auto v = q.front();
      q.pop();

      if (visited[v]) continue;
      visited[v] = true;

      for (auto& vi: V[v]) {
        if (!visited[vi]) q.push(vi);
      }
    }

    ans += std::count(visited.begin(), visited.end(), true);
  }

  cout << ans << endl;
  return 0;
}
