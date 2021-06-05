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
  int N, K, a;
  cin >> N >> K;
  vector<long long> V1, V2;
  V1.push_back(0);
  V2.push_back(0);
  for (int i = 0; i < N; i++) {
    cin >> a;
    if (a > 0) {
      V1.push_back(a);
    } else {
      V2.push_back(-a);
    }
  }
  sort(V2.begin(), V2.end());

  long long ans = 1e18;

  for (int i = 0; i < V1.size(); i++) {
    int k2 = K-i;
    if (k2 < V2.size()) {
      ans = min(ans, V1[i] + 2*V2[k2]);
    }
  }

  for (int i = 0; i < V2.size(); i++) {
    int k2 = K-i;
    if (k2 < V1.size()) {
      ans = min(ans, V2[i] + 2*V1[k2]);
    }
  }

  cout << ans << endl;
  return 0;
}
