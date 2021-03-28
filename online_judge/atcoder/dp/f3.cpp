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

int lcs[3001][3001];

int main()
{
  string s, t;
  cin >> s >> t;

  for (int i = 0; i < 3001; i++) {
    fill(lcs[i], lcs[i] + 3001, 0);
  }

  for (int i = 0; i < s.length(); i++) {
    for (int j = 0; j < t.length(); j++) {
      if (s[i] == t[j]) {
        lcs[i + 1][j + 1] = lcs[i][j] + 1;
      } else {
        lcs[i + 1][j + 1] = max(lcs[i][j + 1], lcs[i + 1][j]);
      }
    }
  }

  int i = s.length()-1;
  int j = t.length()-1;
  vector<char> v;
  while (i >= 0 && j >= 0) {
    if (s[i] == t[j]) {
      v.push_back(s[i]);
      i--;
      j--;
    } else if (lcs[i][j + 1] > lcs[i + 1][j]) {
      i--;
    } else {
      j--;
    }
  }
  reverse(v.begin(), v.end());

  for (auto& vi: v) {
    cout << vi;
  };
  puts("");

  // cout << lcs[s.length()][t.length()] << endl;

  return 0;
}
