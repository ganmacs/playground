#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

long long L = 1e18;

int main()
{
  int N, M, a, b, c;
  long long ans = 0;
  cin >> N >> M;

  vector<vector<long long>> D(N + 1, vector(N + 1, L));

  for (int i = 0; i < N; i++) {
    D[i][i] = 0;
  }

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    a--;b--;
    D[a][b] = c;
  }

  for (int k = 0; k < N; k++) {
    for (int s = 0; s < N; s++) {
      for (int t = 0; t < N; t++) {
        D[s][t] = min(D[s][t], D[s][k] + D[k][t]);
      }
    }

    for (int s = 0; s < N; s++) {
      for (int t = 0; t < N; t++) {
        if (D[s][t] < L) ans += D[s][t];
      }
    }
  }

  cout << ans << endl;
  return 0;
}
