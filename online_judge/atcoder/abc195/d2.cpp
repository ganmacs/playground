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
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<pair<int, int> > bag(N);
  for (auto& v: bag) {
    cin >> v.first >> v.second;
  }
  sort(bag.begin(), bag.end());

  vector<int> X(M);
  for (auto& vi: X) {
    cin >> vi;
  };

  for (int i = 0; i < Q; i++) {
    int L, R;
    cin >> L >> R;

    vector<int> box(X.begin(), X.begin() + L - 1);
    box.insert(box.end(), X.begin() + R, X.end());
    sort(box.begin(), box.end());
    priority_queue<int> q;
    int ans = 0;
    auto ba = bag.begin();
    for (auto& bi: box) {
      while (ba != bag.end() && ba->first <= bi) {
        q.push(ba->second);
        ba++;
      }

      if (!q.empty()) {
        ans += q.top();
        q.pop();
      }
    };

    cout << ans << endl;
  }

  return 0;
}
