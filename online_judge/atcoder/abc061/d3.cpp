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

const long long INF = 1e18;
long long d[10000];

int main()
{
  long long N, M, a, b, c;
  cin >> N >> M;
  vector<pair<long long, pair<long long, long long>>> V;


  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    V.push_back(make_pair(a-1, make_pair(b-1, -c)));
  }

  fill(d, d + N, INF);
  d[0] = 0;

  for (int i = 0; i < N; i++) {
    for (auto& vi: V) {
      auto s = vi.first;
      auto t = vi.second.first;
      auto c = vi.second.second;

      if (d[s] != INF && d[t] > d[s] + c) {
        d[t] = d[s] + c;
      }
    };
  }

  for (int i = 0; i < N; i++) {
    for (auto& vi: V) {
      auto s = vi.first;
      auto t = vi.second.first;
      auto c = vi.second.second;

      if (d[s] != INF && d[t] > d[s] + c) {
        d[t] = d[s] + c;

        if ((N-1) == i && t == (N-1)) {
          cout << "inf" << endl;
          return 0;
        }
      }
    };
  }

  cout << -d[N-1] << endl;
  return 0;
}
