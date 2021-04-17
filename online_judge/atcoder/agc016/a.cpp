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

int main()
{
  string s;
  cin >> s;
  int N = s.length();
  map<char, int> M;

  for (int i = 0; i < N; i++) {
    if (M.find(s[i]) == M.end()) {
      M[s[i]] = i;
    }
  }

  int ans = 1e9;
  for (auto& vi: M) {
    auto k = vi.first;
    int tans = 0;
    for (int i = 0; i < N;) {
      int j = i;
      while (j < N && s[j] != k) {
        j++;
      }

      tans = max(j-i, tans);
      j++;
      i = j;
    }
    ans = min(ans, tans);
  };

  cout << ans << endl;


  return 0;
}

// alk
// lk
// ll
// lk
// lk

// 26, 3
// 25, 3 + 3
// 24, 3 + 3 + 3
// 23, 3 + 3 + 3 + 3
