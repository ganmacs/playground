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

int lcs[3005][3005];

int main()
{
  string s, t;
  cin >> s >> t;

  for (int i = 0; i < 3005; i++) {
    lcs[i][0] = 0;
    lcs[0][i] = 0;
  }

  for (int i = 0; i < s.length(); i++) {
    for (int j = 0; j < t.length(); j++) {
      if (s[i] == t[j]) {
        lcs[i + 1][j + 1] = max(lcs[i + 1][j], max(lcs[i][j + 1], lcs[i][j] + 1));
      } else {
        lcs[i + 1][j + 1] = max(lcs[i + 1][j], lcs[i][j + 1]);
      }
    }
  }

  // for (int i = 0; i < s.length(); i++) {
  //   for (int j = 0; j < t.length(); j++) {
  //     cout << lcs[i + 1][j + 1] << " ";
  //   }
  //   puts("");
  // }

  // for (int i = 0; i < t.length(); i++) {
  //     cout << t[i] << " ";
  // }
  // puts("");

  vector<char> v;
  int i = s.length();
  int j = t.length();
  while (i >= 1 && j >= 1) {
    if (s[i-1] == t[j-1]) {
      v.push_back(t[j-1]);
      i--;
      j--;
    } else if (lcs[i][j-1] > lcs[i-1][j]) {
      j--;
    } else {
      i--;
    }
  }

  reverse(v.begin(), v.end());
  for (auto vi: v) {
    cout << vi;
  }
  puts("");

  return 0;
}
