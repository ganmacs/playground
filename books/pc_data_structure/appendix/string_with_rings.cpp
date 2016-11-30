#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
#include <cmath>
#include <stack>

using namespace std;

vector<int> vec[101];
bool vist[101];
int n;
int maxv;
int max_n;

void dfs(int v, int d)
{
  maxv = max(maxv, d);
  for (int i = 0; i < (int)vec[v].size(); i++) {
    int next = vec[v][i];
    if (vist[next]) continue;
    vist[next] = true;
    dfs(next, d + 1);
    vist[next] = false;
  }
}

int main(){
  while (cin >> n, n) {
    fill_n(vist, 101, false);
    for (int i = 0; i < 101; i++) vec[i].clear();

    set<int> s;
    int a, b;
    for (int i = 0; i < n; i++) {
      cin >> a >> b;
      s.insert(a); s.insert(b);
      vec[a].push_back(b);
      vec[b].push_back(a);
    }

    maxv = 0;
    for(set<int>::iterator it = s.begin(); it != s.end(); it++) {
      vist[*it] = true;
      dfs(*it, 1);
      vist[*it] = false;
    }

    cout << maxv << endl;
  }
}
