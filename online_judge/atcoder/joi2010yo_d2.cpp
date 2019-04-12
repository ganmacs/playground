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

int N, C, a[100];
set<int> S;

void dfs(int v, int used, int r) {
  if (r == C) {
    S.insert(v);
    return;
  }

  for (int i = 0; i < N; i++) {
    if (used & (1 << i)) continue;
    if (a[i]>9) {
      dfs(v*100+a[i], used|(1 << i), r + 1);
    } else {
      dfs(v*10+a[i], used|(1 << i), r + 1);
    }
  }
}

int main(int argc, char *argv[])
{
  cin >> N >> C;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  dfs(0, 0, 0);
  cout << S.size() << endl;
  return 0;
}
