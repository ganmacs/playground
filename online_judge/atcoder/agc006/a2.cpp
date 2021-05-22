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
  string s, t;
  cin >> N >> s >> t;

  int ans = (s + t).size();

  for (int i = 0; i < s.size(); i++) {
      bool f = true;

    for (int j = 0; (j + i) < s.size() && j < t.size(); j++) {
      if (s[i + j] != t[j]) {
        f = false;
        break;
      }
    }

    if (f) {
      int ns = (s.substr(0, i) + t).size();
      ans = min(ns, ans);
    }
  }

  cout << ans << endl;
  return 0;
}
