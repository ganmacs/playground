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
  vector<long long> x(N), y(N), h(N);

  for (int i = 0; i < N; i++) {
    cin >> x[i] >> y[i] >> h[i];
  }

  if (h[0] == 0) {
    for (int i = 0; i < N; i++) {
      if (h[i] != 0) {
        swap(x[0], x[i]);
        swap(y[0], y[i]);
        swap(h[0], h[i]);
      }
    }
  }

  for (long long cx = 0; cx <= 100; cx++) {
    for (long long cy = 0; cy <= 100; cy++) {

      long long H = -1;
      bool t = true;
      for (int i = 0; i < N; i++) {
        long long xxyy = abs(x[i]-cx) + abs(y[i]-cy);

        if (h[i] == 0) {
          if (H > xxyy) {
            t = false;
            break;
          }
        } else {
          long long vv = h[i] + xxyy;
          if (H != -1 && (vv < 1 || vv != H)) {
            t = false;
            break;
          }

          H = vv;
        }
      }

      if (t) {
        printf("%lld %lld %lld\n", cx, cy, H);
        return 0;
      }

    }
  }

  return 0;
}
