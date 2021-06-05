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

int main()
{
  int N, M;
  long long a, b, c;
  map<long long, long long> MA;
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    cin >> a;
    MA[-a]++;
  }

  for (int i = 0; i < M; i++) {
    cin >> b >> c;
    MA[-c] += b;
  }

  long long ans = 0;

  for (auto& vi: MA) {
    if (vi.second <= N) {
      N -= vi.second;
      ans += (-vi.first)*vi.second;
    } else {
      ans += (-vi.first)*N;
      N = 0;
    }

    if (N == 0) break;
  }

  cout << ans << endl;
  return 0;
}
