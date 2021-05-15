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

unsigned long long combination(int n, int r) {
  unsigned long long num = 1;
  for (int i = 1; i <= r; i++) {
    num = num * (n - i + 1) / i;
  }
  return num;
}


int main()
{
  int N, P;
  cin >> N >> P;
  int n0 = 0, n1 = 0;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
    if (vi % 2 == 0) {
      n0++;
    } else {
      n1++;
    }
  };

  if (P % 2 == 0 && n0 == 0 && n1 == 1) {
    cout << 0 << endl;
    return 0;
  } else if (P % 2 == 1 && n1 == 0) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long ans = pow(2, n0);
  unsigned long long t = 0;
  for (int i = P % 2; i <= n1; i += 2) {
    t += combination(n1, i);
  }
  cout << ans*t << endl;
  return 0;
}
