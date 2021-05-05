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

const long long L = 1e18;

int main()
{
  int N, M, P, a, b, c ;
  cin >> N >> M >> P;
  vector<pair<long long, pair<long long, long long>>> V;
  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    V.push_back(make_pair(a-1, make_pair(b-1, -(c-P))));
  }

  long long d[5000];
  fill(d, d + N, L);

  d[0] = 0;

  for (int k = 0; k <= N; k++) {
    for (auto& vi: V) {
      long long s = vi.first;
      long long t = vi.second.first;
      long long c = vi.second.second;

      if (d[s] != L && d[s] + c < d[t]) {
        d[t] = d[s] + c;
      }
    }
  }

  long long ans = max(-d[N-1], (long long)0);

  for (int k = 0; k <= N; k++) {
    for (auto& vi: V) {
      long long s = vi.first;
      long long t = vi.second.first;
      long long c = vi.second.second;

      if (d[s] != L && d[s] + c < d[t]) {
        d[t] = -L;

        if (t == N-1) {
          cout << -1 << endl;
          return 0;
        }
      }
    }
  }


  cout << ans << endl;

  return 0;
}
