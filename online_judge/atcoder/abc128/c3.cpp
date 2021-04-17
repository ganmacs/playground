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

int K[11], P[11];
vector<int> S[11];

int main()
{
  int N, M, ans = 0, a;
  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    cin >> K[i];
    for (int j = 0; j < K[i]; j++) {
      cin >> a;
      S[i].push_back(a);
    }
  }
  for (int i = 0; i < M; i++) cin >> P[i];

  for (int i = 0; i < pow(2, N); i++) {
    vector<int> V;
    for (int j = 0; j < N; j++) {
      if ((1 << j) & i) {
        V.push_back(1);
      } else {
        V.push_back(0);
      }
    }

    bool ok = true;
    for (int j = 0; j < M; j++) {
      int aa = 0;
      for (auto& vi: S[j]) {
        aa += V[vi-1];
      };
      if (aa % 2 != P[j]) {
        ok = false;
        break;
      }
    }

    if (ok) {
      ans++;
    }
  }

  cout << ans << endl;
  return 0;
}
