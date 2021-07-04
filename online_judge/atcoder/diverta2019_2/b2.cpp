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
  vector<long long> X(N), Y(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  if (N == 1) {
    printf("%d\n", 1);
    return 0;
  }

  map<long long, map<long long, int>> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      long long xx = X[i]-X[j];
      long long yy = Y[i]-Y[j];
      M[xx][yy]++;
    }
  }

  int ans = 1e8;
  for (auto& vi: M) {
    for (auto& vii: vi.second) {
      ans = min(ans, N-vii.second);
    }
  }

  cout << ans << endl;
  return 0;
}
