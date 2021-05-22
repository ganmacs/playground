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
  string S;
  cin >> N >> S;
  vector<int> L(N + 1, 0), R(N + 1, 0);

  if (S[0] == 'W') L[0] = 1;
  for (int i = 1; i < N; i++) {
    if (S[i] == 'W') {
      L[i] = L[i-1] + 1;
    } else {
      L[i] = L[i-1];
    }
  }

  if (S[N-1] == 'E') R[N-1] = 1;
  for (int i = N-2; i >= 0; i--) {
    if (S[i] == 'E') {
      R[i] = R[i+1] + 1;
    } else {
      R[i] = R[i+1];
    }
  }

  int ans = 1e9;
  for (int i = 0; i < N; i++) {
    ans = min(ans, R[i] + L[i] -1);
  }
  cout << ans << endl;
  return 0;
}
