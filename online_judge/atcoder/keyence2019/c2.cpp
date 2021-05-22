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
  int N;
  cin >> N;
  vector<int> A(N), B(N), VV;
  for (auto& vi: A) cin >> vi;
  for (auto& vi: B) cin >> vi;

  long long ans = 0;
  long long rest = 0, targ = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] > B[i]) {
      rest += (A[i] - B[i]);
      VV.push_back(-(A[i] - B[i]));
    } else if (A[i] == B[i]) {
      continue;
    } else {
      targ += (B[i] - A[i]);
      ans++;
    }
  }

  if (targ == 0) {
    cout << 0 << endl;
    return 0;
  } else if (targ > rest) {
    cout << -1 << endl;
    return 0;
  }
  sort(VV.begin(), VV.end());

  for (auto& vi: VV) {
    ans++;
    if (targ <= -vi) break;

    targ += vi;
  }

  cout << ans << endl;
  return 0;
}
