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
  int N, M, Q, L, R;
  cin >> N >> M >> Q;
  vector<pair<int, int>> V(N);
  vector<int> X(M);

  for (auto& vi: V) cin >> vi.first >> vi.second;
  for (auto& vi: X) cin >> vi;
  sort(V.begin(), V.end());

  for (int i = 0; i < Q; i++) {
    cin >> L >> R;
    vector<int> vec(X.begin(), X.begin() + L - 1);
    vec.insert(vec.end(), X.begin() + R, X.end());
    sort(vec.begin(), vec.end());
    long long ans = 0;
    priority_queue<int> q;
    int j = 0;
    for (auto& vi: vec) {
      while (j <= V.size() && V[j].first <= vi) {
        q.push(V[j].second);
        j++;
      }

      if (!q.empty()) {
        ans += q.top();
        q.pop();
      }
    }

    cout << ans << endl;
  }
  return 0;
}
