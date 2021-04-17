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

unsigned long long cc(int n, int r){
  unsigned long long num = 1;
  for (int i = 1; i <= r; i++) {
    num = num * (n - i + 1) / i;
  }
  return num;
}

int main()
{
  int N, P, n0 = 0, n1 = 0, a;
  cin >> N >> P;
  for (int i = 0; i < N; i++) {
    cin >> a;
    if (a % 2 == 0) {
      n0++;
    } else {
      n1++;
    }
  }

  unsigned long long ans = 0;
  unsigned long long v0 = 1 << n0;

  if (n1 == 0 && P == 1) {
    ans = 0;
  } else if (P == 0) {
    for (int i = 0; i <= n1; i += 2) {
      ans += cc(n1, i);
    }
  } else {
    for (int i = 1; i <= n1; i += 2) {
      ans += cc(n1, i);
    }
  }

  cout << ans*v0 << endl;

  return 0;
}
