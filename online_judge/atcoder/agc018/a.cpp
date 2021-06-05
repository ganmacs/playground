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
  int N, K, a, m;
  cin >> N >> K;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> a;
    m = max(m, a);

    ans = gcd(ans, a);
  }

  if (K % ans == 0 && m >= K) {
    puts("POSSIBLE");
  } else {
    puts("IMPOSSIBLE");
  }

  return 0;
}
