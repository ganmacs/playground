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

int d[112345], d2[112345];

int main()
{
  int N, Q, l, r;
  string S;
  cin >> N >> Q;
  cin >> S;

  fill(d, d + S.length() + 1, 0);
  for (int i = 1; i < S.length(); i++) {
    d[i] = (S[i-1] == 'A' && S[i] == 'C');
  }

  d2[0] = 0;
  for (int i = 0; i < S.length(); i++) {
    d2[i + 1] = d2[i] + d[i];
  }

  // for (int i = 0; i < S.length(); i++) {
  //   cout << d[i] << " ";
  // }
  // puts("");
  // for (int i = 0; i <= S.length(); i++) {
  //   cout << d2[i] << " ";
  // }
  // puts("");

  for (int i = 0; i < Q; i++) {
    cin >> l >> r;
    cout << (d2[r] - d2[l]) << endl;
  }

  return 0;
}
