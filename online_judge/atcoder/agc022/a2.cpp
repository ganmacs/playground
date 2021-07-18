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


char next(string str, char s)
{
  for (char i = s; i <= 'z'; i++) {
    bool ff = false;
    for (auto& vi: str) {
      if (vi == i) {
        ff = true;
        break;
      }
    }

    if (!ff) return i;
  }

  return '?';
}


int main()
{
  string S;

  cin >> S;
  int N = S.length();
  if (N < 26) {
    cout << S << next(S, 'a') << endl;
    return 0;
  }

  if (S == "zyxwvutsrqponmlkjihgfedcba") {
    cout << -1 << endl;
    return 0;
  }

  string t(26, 'z');

  for (int i = 0; i < N; i++) {
    if (S[i] == 'z') continue;

    string ttt = S.substr(0, i + 1);

    char n = next(ttt, (char)(ttt[i] + 1));
    if (n == '?') continue;
    ttt[i] = n;

    if (t > ttt) {
      t = ttt;
    }
  }

  cout << t << endl;
  return 0;
}
