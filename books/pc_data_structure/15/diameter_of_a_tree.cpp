#include <cstdio>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MAX = 100000;
const int INF = 1 << 30;
int n, depth[MAX];
stack<int> S;
vector<pair<int, int> > V[MAX];

void dfs(int c)
{
  S.push(c);
  depth[c] = 0;

  int next;
  pair<int, int> p;
  while (!S.empty()) {
    next = S.top(); S.pop();

    for (int i = 0; i < (int)V[next].size(); i++) {
      p = V[next][i];
      if (depth[p.first] == INF) {
        S.push(p.first);
        depth[p.first] = p.second + depth[next];
      }
    }
  }
}

int find_index()
{
  int val = 0, x = 0;
  for (int i = 0; i < n; i++) {
    if (depth[i] == INF) continue;
    if (val < depth[i]) {
      val = depth[i];
      x = i;
    }
  }
  return x;
}

int main()
{
  int s, t, w;
  cin >> n;

  for (int i = 0; i < n-1; i++) {
    cin >> s >> t >> w;
    V[s].push_back(make_pair(t, w));
    V[t].push_back(make_pair(s, w));
  }

  for (int i = 0; i < n; i++) depth[i] = INF;
  dfs(0);
  int idx = find_index();

  for (int i = 0; i < n; i++) depth[i] = INF;
  dfs(idx);
  idx = find_index();

  cout << depth[idx] << endl;
}
