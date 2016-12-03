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
static const int MAX = 5000;

vector<int> vec[MAX];
int ts[MAX];
vector<int> ans;
queue<int> q;

int main(){
  int N, M, w, l;
  cin >> N >> M;
  fill_n(ts, N, 0);

  for (int i = 0; i < M; i++) {
    cin >> w >> l;
    vec[w-1].push_back(l-1);
    ts[l-1]++;
  }

  for (int i = 0; i < N; i++) {
    if (ts[i] == 0) q.push(i);
  }

  bool f = false;
  while (!q.empty()) {
    if (q.size()>1)f |= true;
    int v = q.front(); q.pop();
    ans.push_back(v);

    for (int j = 0; j < (int)vec[v].size(); j++) {
      int vv = vec[v][j];
      ts[vv]--;
      if (!ts[vv]) {
        q.push(vv);
      }
    }
  }

  for (int i = 0; i < (int)ans.size(); i++) {
    printf("%d\n", ans[i] + 1);
  }

  printf("%d\n", f);
}
