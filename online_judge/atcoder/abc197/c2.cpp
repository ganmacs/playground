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
  int N;
  cin >> N;
  unsigned long long ans = 1e19;
  vector<unsigned long long> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  unsigned long long k, l;
  for (int i = 0; i < pow(2, N); i++) {
    k = 0, l = 0;;

    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        l ^= k;
        k = V[j];
      } else {
        k |= V[j];
      }
    }
    ans = min(ans, l ^ k);
  }

  cout << ans << endl;
  return 0;
}
