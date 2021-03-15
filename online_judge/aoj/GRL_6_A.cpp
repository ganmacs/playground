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

int V, M;
int E[108][108];
bool used[108];

int sss(int s, int g, int v) {
  if (s == g) {
    return v;
  }
  used[s] = true;

  for (int i = 0; i < M; i++) {
    if (E[s][i] <= 0 || used[i]) continue;

    auto vvv = sss(i, g, min(v, E[s][i]));
    if (vvv) {
      E[i][s] += vvv;
      E[s][i] -= vvv;
      return vvv;
    }
  }

  return 0;
}


int main()
{
  cin >> V >> M;
  for (int i = 0; i < M; i++) {
    fill(E[i], E[i] + M, 0);
  }

  int a, b, c;
  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    E[a][b] = c;
  }

  int ans = 0;
  while (true) {
    fill(used, used + M, false);
    auto v = sss(0, V-1, 1e9);

    // for (int i = 0; i < M; i++) {
    //   for (int j = 0; j < M; j++) {
    //     cout << E[i][j] << " ";
    //   }
    //   puts("");
    // }

    if (v == 0) {
      break;
    }
    ans += v;
  }

  cout << ans << endl;
  return 0;
}
