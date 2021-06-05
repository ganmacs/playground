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

  int d[112345];
  vector<int> V1, V2;
  int N, K, a;

  cin >> N >> K;
  V1.push_back(0);
  V2.push_back(0);
  for (int i = 0; i < N; i++) {
    cin >> a;
    if (a < 0) {
      V1.push_back(-a);
    } else {
      V2.push_back(a);
    }
  }
  sort(V1.begin(), V1.end());

  int n1 = V1.size();
  int n2 = V2.size();
  long long ans = 1e18;

  for (int i = 0; i < n1; i++) {
    int j = K-i;
    if (j >= 0 && j < n2) {
      ans = min(ans, (long long)V1[i]*2 + V2[j]);
    }
  }

  for (int i = 0; i < n2; i++) {
    int j = K-i;
    if (j >= 0 && j < n1) {
      ans = min(ans, (long long)V2[i]*2 + V1[j]);
    }
  }

  cout << ans << endl;
  return 0;
}
