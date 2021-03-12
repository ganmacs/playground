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

int A[312345], B[312345];

int main()
{
  int N;
  string S;
  cin >> N >> S;

  A[0] = 0;
  B[N] = 0;
  for (int i = 0; i < S.length(); i++) {
    A[i + 1] = A[i] + (S[i] == 'W');
    B[N - (i + 1)] = B[N - i] + (S[N-i-1] == 'E');
  }

  int ans = 1e9;
  for (int i = 0; i < N; i++) {
    ans = min(ans, A[i + 1] + B[i] -1);
  }

  cout << ans << endl;
  return 0;
}
