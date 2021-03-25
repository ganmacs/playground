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

long long int MA[2000];

int main()
{
  int N, M, a, b;
  long long c;
  cin >> N >> M;
  vector<pair<int, pair<int, long long> > > E(M);

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    E[i] = make_pair(a-1, make_pair(b-1, -c));
  }

  fill(MA, MA + N, 1e18);
  MA[0] = 0;
  for (int i = 0; i < N; i++) {
    for (auto& vi: E) {
      auto t = vi.first;
      auto next = vi.second.first;
      auto cost = vi.second.second;
      if (MA[t] != 1e18 && MA[t] + cost < MA[next]) {
        MA[next] = MA[t] + cost;
      }
    };
  }

  for (int i = 0; i < N; i++) {
    for (auto& vi: E) {
      auto t = vi.first;
      auto next = vi.second.first;
      auto cost = vi.second.second;

      if (MA[t] + cost < MA[next]) {
        MA[next] = MA[t] + cost;
        if (i == N-1 && next == N-1) {
          cout << "inf" << endl;
          return 0;
        }
      }
    };
  }

  cout << -MA[N-1] << endl;
  return 0;
}
