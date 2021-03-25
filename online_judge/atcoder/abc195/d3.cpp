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

bool used[100];

int main()
{
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<pair<int, int> > V(N);
  vector<int> X(M);

  int w, v;
  for (auto& vi: V) {
    cin >> w >> v;
    vi.first = -v;
    vi.second = w;
  };

  for (auto& vi: X) {
    cin >> vi;
  };

  sort(V.begin(), V.end());

  int L, R;
  for (int i = 0; i < Q; i++) {
    cin >> L >> R;
    vector<int> vvv;
    vvv.insert(vvv.end(), X.begin(), X.begin() + L - 1);
    vvv.insert(vvv.end(), X.begin() + R, X.end());
    sort(vvv.begin(), vvv.end());

    fill(used, used + N, false);
    long long int ans = 0;
    for (int i = 0; i < vvv.size(); i++) {
      for (int j = 0; j < N; j++) {
        if (!used[j] && vvv[i] >= V[j].second) {
          ans += -V[j].first;
          used[j] = true;
          break;
        }
      }
    }

    cout << ans << endl;
  }

  return 0;
}
