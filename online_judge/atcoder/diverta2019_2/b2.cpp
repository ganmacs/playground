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
  int N, ans = N;
  cin >> N;
  vector<int> X(N), Y(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  if (N == 1) {
    cout << 1 << endl;
    return 0;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      int xx = X[i] - X[j];
      int yy = Y[i] - Y[j];

      int a = 0;
      for (int i2 = 0; i2 < N; i2++) {
        for (int j2 = 0; j2 < N; j2++) {
          if (i2 == j2) continue;
          int xx2 = X[i2] - X[j2];
          int yy2 = Y[i2] - Y[j2];

          if (xx == xx2 && yy2 == yy) a++;
        }
      }
      ans = min(ans, N-a);
    }
  }

  cout << ans << endl;
  return 0;
}
