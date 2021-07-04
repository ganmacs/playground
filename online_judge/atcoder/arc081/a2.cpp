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
  int N, a;
  cin >> N;
  map<long long, int> M;
  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  }
  vector<pair<long long, int>> V;

  for (auto& vi: M) {
    if (vi.second < 2) continue;
    V.push_back({ vi.first, vi.second });
  }

  if (V.size() == 0) {
    printf("%d\n", 0);
    return 0;
  }

  sort(V.begin(), V.end(), greater<pair<long long, int>>());

  int t = 0;
  long long ans = 1;

  for (auto& vi: V) {
    while (vi.second >= 2) {
      ans *= vi.first;
      vi.second -= 2;
      t++;
      if (t == 2) {
        cout << ans << endl;
        return 0;
      }
    }
  }

  printf("%d\n", 0);

  return 0;
}
