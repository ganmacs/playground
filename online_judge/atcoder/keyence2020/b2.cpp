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
  int N;
  cin >> N;
  vector<long long> X(N), L(N);
  vector<pair<long long, long long>> K(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> L[i];
    K[i] = {X[i] + L[i],  X[i] - L[i]};
  }
  sort(K.begin(), K.end());

  long long t = -1e18;
  int ans = N;

  for (auto& ki: K) {
    if (ki.second < t) {
      ans--;
    } else {
      t = ki.first;
    }
  }
  cout << ans << endl;
  return 0;
}
