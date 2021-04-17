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

int d[112345];

int main()
{
  int N, Q, l, r;
  string S;
  cin >> N >> Q;
  cin >> S;

  d[0] = 0;
  for (int i = 1; i < N; i++) {
    if (S[i-1] == 'A' && S[i] == 'C') {
      d[i] = d[i-1] + 1;
    } else {
      d[i] = d[i-1];
    }
  }

  for (int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    l--;r--;
    cout << (d[r]-d[l]) << endl;
  }

  return 0;
}
