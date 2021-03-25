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
  long long int Q, H, S, D, N, ans = 1e18;
  cin >> Q >> H >> S >> D >> N;
  Q *= 4;
  H *= 2;

  if (N%2 == 0) {
    auto v = min(min(Q*2, H*2), min(S*2, D));
    cout << (v * (N/2)) << endl;
  } else {
    auto v = min(min(Q, H), S);
    cout << min(v + D*(N/2), v*N) << endl;
  }

  return 0;
}
