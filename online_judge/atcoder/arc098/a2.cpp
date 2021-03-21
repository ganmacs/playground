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

int D1[312345], D2[312345];

int main()
{
  int N, ans = 1e9;
  string S;
  cin >> N >> S;

  D2[N] = 0;
  for (int i = 0; i < N; i++) {
    D1[i] = (S[i] == 'W');
    if (i >= 1) D1[i] += D1[i-1];

    D2[N - (i + 1)] = D2[N - i] + (S[N-(i+1)] == 'E');
  }

  for (int i = 0; i < N; i++) {
    ans = min(ans, D2[i] + D1[i] - 1);
  }

  cout << ans << endl;

  return 0;
}
