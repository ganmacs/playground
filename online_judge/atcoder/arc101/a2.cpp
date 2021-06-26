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
  int N, K;
  long long a;
  vector<long long> V1, V2;
  cin >> N >> K;
  V1.push_back(0);
  V2.push_back(0);
  for (int i = 0; i < N; i++) {
    cin >> a;
    if (a >= 0) {
      V1.push_back(a);
    } else {
      V2.push_back(-a);
    }
  }
  sort(V2.begin(), V2.end());

  long long ans = 1e18;
  int S1 = V1.size();
  int S2 = V2.size();

  for (int i = 0; i < min(S1, K + 1); i++) {
    if ((K-i) < 0 || (K-i) >= S2) continue;
    ans = min(V2[K-i]*2 + V1[i], ans);
  }

  for (int i = 0; i < min(S2, K + 1); i++) {
    if ((K-i) < 0 || (K-i) >=  S1) continue;

    ans = min(V1[K-i]*2 + V2[i], ans);
  }

  cout << ans << endl;
  return 0;
}
