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
  string s, t;
  cin >> s >> t;

  // int ans = s.length() + t.length();
  for (int i = 0; i < N; i++) {
    bool ok = true;
    for (int j = 0; (j + i) < N; j++) {
      if (s[i + j] != t[j]) {
        ok = false;
        break;
      }
    }

    if (ok) {
      auto k = N-i;
      cout << 2*N-k << endl;
      return 0;
    }
  }

  cout << (N*2) << endl;
  return 0;
}
