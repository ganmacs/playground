#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = (1 << 30);
const int MAX = 100000;

int n, e;
vector<int> M[MAX];
bool vist[MAX];
int d[MAX];
vector<int> ans;

void bsf(int i)
{
  queue<int> que;
  vist[i] = true;
  que.push(i);

  while (!que.empty()) {
    int v = que.front(); que.pop();
    ans.push_back(v);

    for (int i = 0; i < (int)M[v].size(); i++) {
      int vv = M[v][i];
      d[vv]--;
      if (d[vv] == 0 && !vist[vv]) {
        vist[vv] = true;
        que.push(vv);
      }
    }
  }
}

void tsort()
{
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (d[i] == 0 && !vist[i]) bsf(i);
  }
}

int main()
{
  int s, t;
  scanf("%d %d", &n, &e);

  for (int i = 0; i < n; i++) {
    d[i] = 0;
    vist[i] = false;
  }

  for (int i = 0; i < e; i++) {
    cin >> s >> t;
    d[t]++;
    M[s].push_back(t);
  }

  tsort();

  for (int i = 0; i < (int)ans.size(); i++) {
    cout << ans[i] << endl;
  }
}
