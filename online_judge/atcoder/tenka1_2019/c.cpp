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
#include <numeric>

using namespace std;

long long d1[212345], d2[212345];

int main()
{
  int N;
  string S;
  cin >> N >> S;

  d1[0] = 0;
  d2[N] = 0;
  for (int i = 0; i < N; i++) {
    d1[i + 1] = d1[i] + (S[i] == '#' ? 1 : 0);
    d2[N-i-1] = d2[N-i] + (S[N-i-1] == '.' ? 1 : 0);
  }

  long long ans = 1e18;
  for (int i = 0; i < N; i++) {
    ans = min(d1[i + 1] + d2[i], ans);
  }

  cout << ans-1 << endl;


  return 0;
}
