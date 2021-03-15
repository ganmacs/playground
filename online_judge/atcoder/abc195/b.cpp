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

// int N[112345];

int main()
{
  int A, B, W, mi = 1e9, ma = 0;
  bool f = false;
  cin >> A >> B >> W;

  W *= 1000;
  for (int i = (W/B); i <= (W/A); i++) {
    double k = (W*1.0)/i;
    if (B >= k && A <= k) {
      f = true;
      mi = min(mi, i);
      ma = max(ma, i);
    }
  }

  if (f) {
    cout << mi << " " << ma << endl;
  } else {
    puts("UNSATISFIABLE");
  }

  return 0;
}
