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
  int K, N;
  cin >> N >> K;

  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  sort(V.begin(), V.end());

  long long int ans = 1e18;
  for (int i = 0; i < V.size() - K + 1; i++) {
    long long int t = 0;
    for (int j = 0; j < K-1; j++) {
      t += (V[i + j + 1] - V[i + j]);
    }
    ans = min(ans, t);
  }

  cout << ans << endl;

  return 0;
}
