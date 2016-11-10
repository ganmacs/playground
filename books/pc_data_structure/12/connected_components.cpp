#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 100000;
vector<int> vec[MAX];
int ans[MAX];
int n, m;

void dfs(int c)
{
  stack<int> S;
  S.push(c);
  ans[c] = c;

  while (!S.empty()) {
    int v = S.top(); S.pop();

    for (int i = 0; i < (int)vec[v].size(); i++) {
      int k = vec[v][i];
      if (ans[k] == -1) {
        S.push(k);
        ans[k] = c;
      }
    }
  }
}

int main()
{
  int s, t, q;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> s >> t;
    vec[s].push_back(t);
    vec[t].push_back(s);
  }

  for (int i = 0; i < n; i++) {
    ans[i] = -1;
  }
  for (int i = 0; i < n; i++) {
    if (ans[i] == -1) dfs(i);
  }

  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> s >> t;
    if (ans[s] == ans[t]) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }

  return 0;
}
