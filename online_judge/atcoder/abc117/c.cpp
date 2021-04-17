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
  int N, M, ans = 0;
  cin >> N >> M;

  vector<long long> V(M);
  for (long long i = 0; i < M; i++) {
    cin >> V[i];
  }
  sort(V.begin(), V.end());

  if (N > M) {
    cout << 0 << endl;
    return 0;
  }

  vector<pair<long long, long long >> d;
  for (int i = 1; i < M; i++) {
    auto v = V[i] - V[i-1];
    d.push_back(make_pair(-v, i-1));
  }
  sort(d.begin(), d.end());

  vector<long long> d2;
  for (int i = 0; i < N-1; i++) {
    d2.push_back(d[i].second);
  }
  sort(d2.begin(), d2.end());

  int i = 0;
  for (int j = 0; j < d2.size(); j++) {
    auto v = d2[j];
    ans += (V[v] - V[i]);
    i = (v + 1);
  }
  ans += (V[M-1] - V[i]);
  cout << ans << endl;

  return 0;
}
