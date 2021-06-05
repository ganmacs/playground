#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N;
  long long K;
  cin >> N >> K;
  map<unsigned long long, unsigned long long> M;
  unsigned long long a, b;

  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    M[a] += b;
  }

  unsigned long long ans = 0;
  for (auto& vi: M) {
    unsigned long long vv = (vi.first - ans);
    if (vv > K) {
      break;
    }

    K = (K - vv) + vi.second;
    ans = vi.first;
  }

  ans += K;
  cout << ans << endl;
  return 0;
}
