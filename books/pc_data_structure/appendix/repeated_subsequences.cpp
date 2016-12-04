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
typedef pair<int,int> P;

int c[400][400];
int from[400][400];

string lcs(string A, string B)
{
  int as = A.size();
  int bs = B.size();
  A = ' ' + A;
  B = ' ' + B;

  for (int i = 0; i <= as; i++) {
    c[i][0] = 0; from[i][0] = -1;
  }
  for (int i = 0; i <= bs; i++) {
    c[0][i] = 0; from[0][i] = -1;
  }

  for (int i = 1; i <= as; i++) {
    for (int j = 1; j <= bs; j++) {
      if (A[i] == B[j]) {
        c[i][j] = c[i-1][j-1] + 1;
        from[i][j] = 2;
      } else if (c[i][j-1] > c[i-1][j]) {
        c[i][j] = c[i][j-1];
        from[i][j] = 1;
      } else {
        c[i][j] = c[i-1][j];
        from[i][j] = 0;
      }
    }
  }

  string s = "";
  int n = as, m = bs;
  while (from[n][m] >= 0) {
    if (from[n][m] == 2) {
      s += A[n];
      n--; m--;
    }
    else if (from[n][m] == 1) { m--; }
    else { n--; }
  }
  reverse(s.begin(), s.end());

  return s;
}

int main()
{
  string S;
  while (cin >> S, S != "#END") {
    string m = "";
    int s = S.size();
    for (int i = 1; i < s; i++) {
      string v = lcs(S.substr(0, i), S.substr(i, s));
      if (v.size() > m.size()) m = v;
    }
    cout << m << endl;
  }
}
