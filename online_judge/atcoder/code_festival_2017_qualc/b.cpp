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

long long int ans = 0;
int V[102];
int N;

void dfs(int i, long long int v)
{
  if (i == N) {
    if (v % 2 == 0) ans++;
    return;
  }

  dfs(i + 1, v*(V[i]-1));
  dfs(i + 1, v*V[i]);
  dfs(i + 1, v*(V[i]+1));
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> V[i];
  };

  dfs(0, 1);
  cout << ans << endl;
  return 0;
}
