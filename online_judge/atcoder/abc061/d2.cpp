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
  int N, M;
  cin >> N >> M;
  vector<pair<long long, pair<long long, long long >>> V(M);
  vector<long long> MA(N, L);
  for (auto& vi: V) {
    cin >> vi.first >> vi.second.first >> vi.second.second;
    vi.first--;
    vi.second.first--;
    vi.second.second = -vi.second.second;
  }

  MA[0] = 0;
  for (int k = 0; k < N; k++) {
    for (auto& vi: V) {
      auto s = vi.first;
      auto t = vi.second.first;
      auto c = vi.second.second;

      if (MA[s] != L && MA[s] + c < MA[t]) {
        MA[t] = MA[s] + c;
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (auto& vi: V) {
      auto s = vi.first;
      auto t = vi.second.first;
      auto c = vi.second.second;

      if (MA[s] != L && MA[s] + c < MA[t]) {
        if (t == (N-1)) {
          puts("inf");
          return 0;
        }
        MA[t] = MA[s] + c;
      }
    }
  }

  cout << -MA[N-1] << endl;
  return 0;
}
