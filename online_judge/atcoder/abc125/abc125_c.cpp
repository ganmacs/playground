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

int N, A[123450];

int main(int argc, char *argv[])
{
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  sort(A, A + N, greater<int>());
  int ng = 0;

  int ans = A[0];
  for (int i = 1; i < N; i++) {
    if (ans <= A[i] && A[i] % ans == 0) continue;
    ng++;
    if (ng >= 2) break;
  }

  if (ng <= 1) {
    cout << ans << endl;
    return 0;
  }

  ans = max(A[1], (ans/2) + 1);
  bool ok = true;
  for (; ans >= 1; ans--) {
    if (ans > A[N-2]) continue;

    ng = 0;
    ok = true;
    for (int i = 0; i < N; i++) {
      if (ans <= A[i] && A[i] % ans == 0) continue;
      ng++;
      if (ng > 1) {
        ok = false;
        break;
      }
    }

    if (ok) {
      cout << ans << endl;
      return 0;
    }
  }

  return 0;
}
