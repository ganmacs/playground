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

const long long L = 1e18;

int main()
{
  int N, M, a, b;
  long long c, ans = 0;
  cin >> N >> M;

  vector<vector<long long>> MA(N, vector(N, L));

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    a--;b--;
    MA[a][b] = c;
  }
  for (int i = 0; i < N; i++) MA[i][i] = 0;

  for (int k = 0; k < N; k++) {
    for (int s = 0; s < N; s++) {
      for (int t = 0; t < N; t++) {
        MA[s][t] = min(MA[s][t], MA[s][k] + MA[k][t]);
        if (MA[s][t] != L) {
          ans += MA[s][t];
        }
      }
    }
  }

  printf("%lld\n", ans);
  return 0;
}
