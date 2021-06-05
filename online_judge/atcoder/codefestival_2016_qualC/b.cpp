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
  int K, T;
  cin >> K >> T;
  vector<int> V(T);
  for (auto& vi: V) {
    cin >> vi;
    vi = -vi;
  }
  sort(V.begin(), V.end());

  long long t = -V[0];
  for (int i = 1; i < T; i++) {
    V[i] = -V[i];
    if (V[i] <= t) {
      t -= V[i];
    } else {
      t = V[i]-t;
    }
  }

  cout << max(t-1, (long long)0) << endl;
  return 0;
}
