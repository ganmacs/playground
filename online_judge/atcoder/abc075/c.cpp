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
map<int, map<int, int>> V;
vector<bool> d(51, false);

void dfs(int n) {
  if (d[n]) return;
  d[n] = true;

  for (auto& vi: V[n]) {
    if (vi.second && !d[vi.first]) {
      dfs(vi.first);
    }
  }
}

int main()
{
  int N, M, a, b, ans = 0;
  cin >> N >> M;
  vector<int> A, B;

  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    a--;b--;
    A.push_back(a);
    B.push_back(b);
    V[a][b]++;
    V[b][a]++;
  }

  for (int i = 0; i < M; i++) {
    a = A[i], b = B[i];
    V[a][b]--;
    V[b][a]--;

    fill(d.begin(), d.end(), false);
    dfs(0);
    if (count(d.begin(), d.end(), true) != N) ans++;

    V[a][b]++;
    V[b][a]++;
  }


  printf("%d\n", ans);
  return 0;
}
