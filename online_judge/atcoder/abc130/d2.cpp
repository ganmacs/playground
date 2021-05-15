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
  unsigned long long ans = 0, N, K, t = 0;
  cin >> N >> K;
  vector<long long> V(N);
  for (auto& vi: V) {
    cin >> vi;
  }

  int j = 0;
  for (int i = 0; i < N; i++) {
    while (j < N && t < K) {
      t += V[j];
      j++;
    }

    if (t < K) {
      break;
    }

    ans += (N - j + 1);
    t -= V[i];
  }

  cout << ans << endl;

  return 0;
}
