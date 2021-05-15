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
  int N, a;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  sort(V.begin(), V.end());

  long long ans = 0;
  for (int a = 0; a < N-2; a++) {
    for (int b = a + 1; b < N-1; b++) {
      int ok = b + 1, ng = N;
      if (!((V[a] < V[b] + V[ok]) && (V[b] < V[ok] + V[a]) && (V[ok] < V[a] + V[b]))) {
        continue;
      }

      while (abs(ok-ng) > 1) {
        int c = (ok + ng)/2;
        if ((V[a] < V[b] + V[c]) && (V[b] < V[c] + V[a]) && (V[c] < V[a] + V[b])) {
          ok = c;
        } else {
          ng = c;
        }
      }

      ans += (ok - b);
    }
  }

  cout << ans << endl;

  return 0;
}
