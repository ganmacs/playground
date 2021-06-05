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

const int INF = 1e9 + 7;

int main()
{
  unsigned long long N, K;
  unsigned long long ans = 0;
  cin >> N >> K;
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;
  unsigned long long ttt = K*(K+1)/2 % INF;
  unsigned long long ttt2 = K*(K-1)/2 % INF;

  for (int i = 0; i < N; i++) {
    unsigned long long t = 0;
    for (int j = i + 1; j < N; j++) {
      if (V[i] > V[j]) t++;
    }

    unsigned long long t2 = 0;
    for (int j = 0; j < i; j++) {
      if (V[i] > V[j]) t2++;
    }

    if (K == 1) {
      ans = (ans + t*K);
    } else {
      ans = (ans + t*ttt + t2*ttt2) % INF;
    }
  }

  cout << ans << endl;
  return 0;
}
