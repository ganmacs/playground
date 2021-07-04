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

const long long L = 998244353;

int main() {
  int N;
  cin >> N;
  vector<int> D(N);
  map<int, int> M;
  for (auto& vi: D) {
    cin >> vi;
    M[vi]++;
  }

  if (D[0] != 0 || M[0] != 1) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long ans = 1;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < M[i]; j++) {
      ans = (ans * M[i-1]) % L;
    }
  }

  cout << ans << endl;

  return 0;
}
