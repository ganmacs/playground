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
#include <numeric>

using namespace std;

int main()
{
  int W, H, N, x, y, a;
  cin >> W >> H >> N;
  int l = 0, r = W, t = H, b = 0;

  for (int i = 0; i < N; i++) {
    cin >> x >> y >> a;

    if (a == 1) {
      l = max(l, x);
    } else if (a == 2) {
      r = min(r, x);
    } else if (a == 3) {
      b = max(b, y);
    } else if (a == 4) {
      t = min(t, y);
    }
  }


  if ((r-l) < 0 || (t-b) < 0) {
    cout << 0 << endl;
  } else {
    cout << max((r-l) * (t-b), 0) << endl;
  }

  return 0;
}
