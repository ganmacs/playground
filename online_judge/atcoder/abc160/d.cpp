#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int
main()
{
  int N, X, Y;
  cin >> N >> X >> Y;
  map<int, int> MA;

  for (int i = 1; i < N; i++) {
    for (int j = i + 1; j <= N; j++) {
      if (i == j) continue;
      auto v = min(j-i, abs(X-i) + 1 + abs(Y-j));
      MA[v]++;
    }
  }
  for (int i = 1; i < N; i++) {
    cout << MA[i] << endl;
  }

  return 0;
}
