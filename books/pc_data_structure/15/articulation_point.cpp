#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100000;
bool vist[MAX];
int n, v;

vector<int> G[MAX];
int prenum[MAX], lowest[MAX];

int dfs(int current, int t)
{
  prenum[current] = lowest[current] = t;
  t++;
  vist[current] = true;


  for (int i = 0; i < (int)G[current].size(); i++) {
    int next = G[current][i];
    if (!vist[v]) {
      t = dfs(next, t);
      // lowest[current] = min(lowest[current], lowest[next]);
    } else {
      // need prev?
    }


  }
  return t;
}

void ap()
{

  dfs(0, 0);
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
