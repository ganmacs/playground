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
  int N;
  cin >> N;
  vector<long long>  V(N);
  for (int i = 0; i < N; i++) {
    cin >> V[i];
    V[i] -= (i + 1);
  }
  sort(V.begin(), V.end());

  long long t, ans = 0;
  if (N%2 == 1) {
    t = V[N/2];
  } else {
    t = (V[N/2] + V[N/2 - 1])/2;
  }

  for (auto& vi: V) {
    ans += abs(vi-t);
  }

  cout << ans << endl;

  return 0;
}
