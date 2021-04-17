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

const unsigned long long int CO = 1e9 + 7;

int main()
{
  unsigned long long N, K;
  cin >> N >> K;
  vector<long long int> V(N);
  for (int i = 0; i < N; i++) {
    cin >> V[i];
  }
  unsigned long long int ans = 0;
  unsigned long long int KKK = K*(K-1)/2 % CO;

  for (int i = 0; i < N; i++) {
    unsigned long long v = 0;
    for (int j = i + 1; j < N; j++) {
      if (V[i] > V[j]) {
        v++;
      }
    }

    unsigned long long v2 = 0;
    if (K != 1) {
      for (int j = 0; j < N; j++) {
        if (V[i] > V[j]) {
          v2++;
        }
      }
    }

    ans += (v*K + v2*KKK);
    ans %= CO;
  }

  cout << ans << endl;
  return 0;
}
