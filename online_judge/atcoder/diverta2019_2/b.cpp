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
  int N;
  cin >> N;
  vector<long long> X(N), Y(N);
  map<pair<long long, long long>, long long> S;

  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  if (N == 1) {
    cout << 1 << endl;
    return 0;
  }

  int ans = N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      long long dy = Y[i]-Y[j];
      long long dx = X[i]-X[j];

      int s = 0;
      for (int i2 = 0; i2 < N; i2++) {
        for (int j2 = 0; j2 < N; j2++) {
          if (i2 == j2) continue;
          // 重複して数えているが任意のXとYはユニークだからおなじ i たいして dx,  dy を持つことはない
          if (dy == Y[i2]-Y[j2] && dx == X[i2]-X[j2]) s++;
        }
      }
      ans = min(ans, N-s);
    }
  }

  cout << ans << endl;
  return 0;
}
