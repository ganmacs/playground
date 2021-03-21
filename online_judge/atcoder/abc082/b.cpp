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
  string s, t;
  cin >> s >> t;

  sort(s.begin(), s.end());
  sort(t.begin(), t.end());

  auto sl = s.length();
  auto tl = t.length();

  for (int i = 0; i < sl; i++) {
    for (int j = 0; j < tl; j++) {
      if (s[i] < t[j]) {
        cout << "Yes" << endl;
        return 0;
      }
    }
  }

  if (sl < tl) {
    map<string, int> m;

    for (auto& vi: t) {
      m[t]++;
    };

    if (m.size() == 1) {
      if (t.substr(0, sl) == s) {
        cout << "Yes" << endl;
        return 0;
      }
    }
  }

  cout << "No" << endl;
  return 0;
}
