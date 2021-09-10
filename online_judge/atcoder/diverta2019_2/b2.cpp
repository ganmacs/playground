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
  map<long long,  map<long long, int>> M;
  cin >> N;
  vector<long long> X(N), Y(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) continue;

      auto x = X[i] - X[j];
      auto y = Y[i] - Y[j];
      M[x][y]++;
    }
  }

  int ans = 1e8;
  for (auto& vi: M) {
    for (auto& vi2: vi.second) {
      ans = min(N-vi2.second, ans);
    }
  }

  printf("%d\n", ans);
  return 0;
}
