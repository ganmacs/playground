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

int main(int argc, char *argv[])
{

  string s;
  cin >> s;
  int len = s.size();
  for (int i = 0; i < (1 << (len-1)); i++) {
    int v = s[0]-'0';

    for (int j = 0; j < (len-1); j++) {
      if (i & (1 << j)) {
        v += (s[j + 1]-'0');
      } else {
        v -= (s[j + 1]-'0');
      }
    }

    if (v == 7) {
      string ans = "";
      ans += s[0];

      for (int j = 0; j < (len-1); j++) {
        if (i & (1 << j)) {
          ans += "+";
          ans += s[j + 1];
          v += (s[j + 1]-'0');
        } else {
          ans += "-";
          ans += s[j + 1];
        }
      }
      printf("%s=7\n", ans.c_str());
      return 0;
    }
  }
}
