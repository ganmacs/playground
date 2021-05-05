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
  long long N, K;
  cin >> N >>  K;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  unsigned long long t = 0;
  long long ans = 0;

  int j = 0;
  for (int i = 0; i < N; i++) {
    while (t < K && j < N) {
      t += V[j];
      j++;
    }
    if (t < K) break;
    ans += (N-j+1);
    t -= V[i];
  }

  cout << ans << endl;
  return 0;
}
