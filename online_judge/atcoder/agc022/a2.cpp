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

char fff(string s, char start) {
  for (char i = start; i <= 'z'; i++) {
    bool t = false;
    for (auto& vi: s) {
      if (vi == i) {
        t = true;
        break;
      }
    }

    if (!t) {
      return i;
    }
  }

  return '0';
}

int main()
{
  string S;
  cin >> S;
  int N = S.length();
  if (N < 26) {
    cout << S << fff(S, 'a') << endl;
    return 0;
  }

  if (S == "zyxwvutsrqponmlkjihgfedcba") {
    cout << -1 << endl;
    return 0;
  }

  string t(26, 'z');
  for (int i = 0; i < N; i++) {
    if (S[i] == 'z') continue;

    string ss = S.substr(0, i + 1);
    char v = fff(ss, (char)(S[i] + 1));
    if (v == '0') {
      continue;
    }

    ss[i] = v;
    if (t > ss) {
      t = ss;
    }
  }
  cout << t << endl;
  return 0;
}
