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

long long kk[112345678];

int main()
{
  int N, K, a;
  cin >> N >> K;
  unsigned long long ans = 0;

  vector<int> V(N);

  kk[0] = 0;

  for (int i = 0; i < N; i++) {
    cin >> a;
    kk[i + 1] = kk[i] + a;
  }

  for (int i = K; i <= N; i++) {
    ans += (kk[i] - kk[i-K]);
  }

  cout << ans << endl;

  return 0;
}
