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
  int N, M;
  cin >> N >> M;
  vector<long long> V(M), V2;
  for (auto& vi: V) {
    cin >> vi;
  }
  sort(V.begin(), V.end());

  if (M == 1) {
    cout << 0 << endl;
    return 0;
  }

  for (int i = 0; i < (M-1); i++) {
    V2.push_back(-(V[i+1]-V[i]));
  }

  sort(V2.begin(), V2.end());
  auto ans = V[M-1] - V[0];
  for (int i = 0; i < (N-1) && i < V2.size(); i++) {
    ans += V2[i];
  }

  cout << ans << endl;
  return 0;
}
