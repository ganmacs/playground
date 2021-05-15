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
  string S, T;
  cin >> S >> T;

  for (int i = 0; i < S.size(); i++) {
    fill(lcs[i], lcs[i] + T.size(), 0);
  }

  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < T.size(); j++) {
      if (S[i] == T[j]) {
        lcs[i + 1][j + 1] = max(lcs[i][j] + 1, lcs[i + 1][j + 1]);
      } else {
        lcs[i + 1][j + 1] = max(lcs[i+1][j], lcs[i][j+1]);
      }
    }
  }

  string ss;
  int i = S.size()-1;
  int j = T.size()-1;
  while (i >= 0 && j >= 0) {
    if (S[i] == T[j]) {
      ss += S[i];
      i--;
      j--;
    } else if (lcs[i][j + 1] > lcs[i + 1][j]) {
      i--;
    } else {
      j--;
    }
  }

  reverse(ss.begin(), ss.end());
  cout << ss << endl;
  return 0;
}
