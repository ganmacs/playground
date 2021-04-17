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
  unsigned long long N, K, ans = 0;;
  cin >> N >> K;
  vector<unsigned long long> V(N);

  for (int i = 0; i < N; i++) {
    cin >> V[i];
  }

  unsigned long long sum = 0;
  int p = 0;
  for (int i = 0; i < N; i++) {
    while (sum < K && p < N) {
      sum += V[p];
      p++;
    }
    if (sum < K) break;
    ans += (N-p+1);
    sum -= V[i];
  }

  cout << ans << endl;

  return 0;
}
