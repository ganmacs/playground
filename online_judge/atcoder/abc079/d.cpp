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

int main()
{
  int H, W;
  cin >> H >> W;
  map<int, vector<pair<int, int>>> D;
  int a, c;
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      cin >> c;
      if (i == j) continue;
      D[i].push_back({ j, c });
    }
  }

  vector<long long> aa(10, 0);
  for (int i = 0; i <= 9; i++) {
    vector<long long> V(10, 1e17);
    priority_queue<pair<long long, int>> que;
    que.push({ 0, i });
    V[i] = 0;
    while (!que.empty()) {
      long long v = -que.top().first;
      int n = que.top().second;
      que.pop();
      if (V[n] < v) continue;

      for (auto& vi: D[n]) {
        int nn = vi.first, c = vi.second;

        if (V[nn] > c + v) {
          V[nn] = c + v;
          que.push({ -V[nn], nn });
        }
      }
    }
    aa[i] = V[1];
  }

  long long ans = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> a;
      if (a == 1 || a == -1) continue;
      ans += aa[a];
    }
  }

  cout << ans << endl;
}
