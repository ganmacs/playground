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

string S;

char first(int l, char mi) {
  for (char c = mi; c <= 'z'; c++) {
    if (S.substr(0, l).find(c) == string::npos) {
      return c;
    }
  }

  return '0';
}

int main()
{
  cin >> S;

  string L(26, 'z');

  if (S.size()<26) {
    cout << S << first(S.size(), 'a') << endl;
    return 0;
  }

  if (S == "zyxwvutsrqponmlkjihgfedcba") {
    cout << -1 << endl;
    return 0;
  }

  string ans = L;
  for (int i = 0; i < S.size(); i++) {
    if (S[i] == 'z') continue;

    char c = first(i + 1, S[i] + 1);
    if (c == '0') continue;

    if (ans > (S.substr(0, i) + c)) {
      ans = S.substr(0, i) + c;
    }
  }

  cout << ans << endl;
  return 0;
}
