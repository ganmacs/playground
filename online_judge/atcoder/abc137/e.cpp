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

long long int d[2501];
bool neg[2501];
const long long int INF = 1e18;

int main()
{
  int N, M, P, a, b, c;
  cin >> N >> M >> P;
  vector<pair<int, pair<int, int> > > e(M);

  for (auto& vi: e) {
    cin >> a >> b >> c;
    vi = make_pair(a-1, make_pair(b-1, -(c-P)));
  };

  fill(d, d + N, INF);
  d[0] = 0;

  for (int i = 0; i < N; i++) {
    for (auto& vi: e) {
      if (d[vi.first] != INF && d[vi.second.first] > vi.second.second + d[vi.first]) {
        d[vi.second.first] =  vi.second.second + d[vi.first];
      }
    };
  }

  fill(neg, neg + N, false);
  for (int i = 0; i < N; i++) {
    for (auto& vi: e) {
      if (d[vi.first] != INF && d[vi.second.first] > vi.second.second + d[vi.first]) {
        d[vi.second.first] = -INF;
      }
    };
  }

  // for (int i = 0; i < N; i++) {
  //   cout << d[i] << " ";
  // }
  // puts("");

  if (-d[N-1] >= INF) {
    cout << -1 << endl;
  } else {
    cout << max((long long int)0, -d[N-1]) << endl;
  }

  return 0;
}
