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
  long long ans = 1e18;
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;

  for (int i = 1; i < pow(2, N); i++) {
    vector<long long> at, tmp;

    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        if (tmp.size() > 0) {
          long long ttt = 0;
          for (auto& vi: tmp) {
            ttt = ttt | vi;
          }
          at.push_back(ttt);
        }

        tmp.clear();
        tmp.push_back(V[j]);
      } else {
        tmp.push_back(V[j]);
      }
    }

    if (tmp.size() > 0) {
      long long ttt = 0;
      for (auto& vi: tmp) {
        ttt = ttt | vi;
      }
      at.push_back(ttt);
    }


    long long t = 0;
    for (auto& vi: at) {
      t = t ^ vi;
    }


    ans = min(t, ans);
  }

  printf("%lld\n", ans);
  return 0;
}
