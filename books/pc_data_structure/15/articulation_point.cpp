#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAX = 100000;
bool vist[MAX];
int n, v;
std::set<int> S;
vector<int> G[MAX];
int prenum[MAX], lowest[MAX];
int tt = 0;

int dfs(int current, int t)
{
  prenum[current] = lowest[current] = t;
  t++;
  vist[current] = true;

  for (int i = 0; i < (int)G[current].size(); i++) {
    int next = G[current][i];
    if (!vist[next]) {
      t = dfs(next, t);

      if (prenum[current] <= lowest[next] && G[current].size() > 1) {
        if (current == 0) tt++;
        if (current == 0 && tt > 1) {
          S.insert(0);
        } else if(current != 0){
          S.insert(current);
        }

      }
      lowest[current] = min(lowest[current], lowest[next]);
    } else {
      lowest[current] = min(lowest[current], prenum[next]);
    }
  }
  return t;
}

void ap()
{
  tt = 0;
  dfs(0, 0);

  for (set<int>::iterator it = S.begin();it != S.end();it++) {
    cout << *it << endl;
  }

}

int main()
{
  int s, t;
  cin >> v >> n;

  for (int i = 0; i < n; i++) {
    cin >> s >> t;
    G[s].push_back(t);
    G[t].push_back(s);
  }

  for (int i = 0; i < n; i++) {
    vist[i] = false;
  }

  ap();
}
