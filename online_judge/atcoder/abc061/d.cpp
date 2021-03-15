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

const long long int INF = 1e18;

long long int d[1002];

int main()
{
  int N, M, a, b, c;
  cin >> N >> M;
  vector<pair<int, pair<int, int> > > G(M);
  for (auto& vi: G) {
    cin >> a >> b >> c;
    vi = make_pair(a-1, make_pair(b-1, -c));
  }

  fill(d, d + N, INF);
  d[0] = 0;
  for (int i = 0; i < N; i++) {
    for (auto& vi: G) {
      if (d[vi.first] != INF && d[vi.second.first] > vi.second.second + d[vi.first]) {
        d[vi.second.first] = vi.second.second + d[vi.first];
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (auto& vi: G) {
      if (d[vi.second.first] > vi.second.second + d[vi.first]) {
        d[vi.second.first] = vi.second.second + d[vi.first];

        if (i == N-1 && vi.second.first == (N-1)) { // goal should be related to the negative loop
          cout << "inf" << endl;
          return 0;
        }
      }
    }
  }

  // for (int i = 0; i < N; i++) {
  //   cout << d[i] << " ";
  // }
  // puts("");

  cout << (-d[N-1]) << endl;
  return 0;
}
