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

  int N, P, n0 = 0, n1 = 0;
  cin >> N >> P;
  vector<int> V;
  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;
    if (a % 2 == 0) {
      n0++;
    } else {
      n1++;
    }
    V.push_back(a);
  }

  unsigned long long ans = 1;

  if (P == 1 && n1 == 0) {
    ans = 0;
  } else if (n1 == 0 && P == 0) {
    for (int i = 0; i < N; i++) {
      ans *= 2;
    }
  } else {
    for (int i = 0; i < N-1; i++) {
      ans *= 2;
    }
  }

  cout << ans << endl;

  return 0;
}
