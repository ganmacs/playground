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

int INF = 1e9;

int main()
{
  int N, ans = 0;;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };
  // V.push_back(0);
  // bool update = false;

  // for (int i = 0; i < N; i++) {
  //   int j = 0, jn = 0, k = INF;
  //   while (jn <= N) {
  //     if (V[jn] == 0) {
  //       if (k != INF) {
  //         for (int l = j; l < jn; l++) {
  //           V[l] -= k;
  //         }
  //         ans += k;
  //         update = true;
  //       }

  //       jn++;
  //       j = jn;
  //       k = INF;
  //     } else {
  //       k = min(k, V[jn]);
  //       jn++;
  //     }
  //   }

  //   if (!update) break;
  // }


  while (true) {
    auto v = -1;
    if (*max_element(V.begin(), V.end()) == 0) break;

    int i = 0;
    while (i < N) {
      if (V[i] == 0) {
        i++;
      } else {
        ans++;
        while (i < N && V[i] > 0) {
          V[i]--;
          i++;
        }
      }
    }
  }

  cout << ans << endl;
  return 0;
}
