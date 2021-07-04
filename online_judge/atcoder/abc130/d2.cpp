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
  long long N, K, ans = 0;
  cin >> N >> K;
  vector<long long> A(N);
  for (auto& vi: A) cin >> vi;


  long long t = 0;
  int j = 0;
  for (int i = 0; i < N; i++) {
    t += A[i];
    if (t < K) continue;

    while (t >= K) {
      ans += (N-i);
      t -= A[j];
      j++;
    }
  }

  cout << ans << endl;
  return 0;
}
