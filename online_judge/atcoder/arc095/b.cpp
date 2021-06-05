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
  cin >> N;
  vector<long long> V(N);
  for (auto& vi: V) {
    cin >> vi;
    vi = -vi;
  }
  sort(V.begin(), V.end());

  int v = -V[0]/2;
  int prev = 1e9;
  int a = 0;
  for (int i = 1; i < N; i++) {
    int vv = min(-V[i], abs(-V[i] + V[0]));
    if (v-vv < prev) {
      a = i;
      prev = v-vv;
    }
  }

  cout << -V[0] << " " << -V[a] << endl;

  return 0;
}
