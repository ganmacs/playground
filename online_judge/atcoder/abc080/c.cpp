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

int main(int argc, char *argv[])
{
  int N;
  cin >> N;
  vector<vector<long long>> P(N, vector(11, 0LL)), F(N, vector(10, 0LL));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 10; j++) {
      cin >> F[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= 10; j++) {
      cin >> P[i][j];
    }
  }

  long long ans = -1e18;

  for (int i = 1; i < pow(2, 10); i++) {
    vector<long long> T;
    long long ta = 0;

    for (int j = 0; j < 10; j++) {
      T.push_back(((1 << j) & i) != 0);
    }

    for (int k = 0; k < N; k++) {
      int tt = 0;
      for (int j = 0; j < 10; j++) {
        if (F[k][j] &&  T[j]) tt++;
      }

      ta += P[k][tt];
    }

    ans = max(ans, ta);
  }

  printf("%lld\n", ans);
  return 0;
}
