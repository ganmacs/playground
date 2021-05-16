#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  string S;
  cin >> S;
  int ans = 0;
  vector<char> a, b, c;
  for (int i = 0; i < 10; i++) {
    if (S[i] == 'o') {
      a.push_back(i + '0');
    } else if (S[i] == 'x') {
      b.push_back(i + '0');
    } else {
      c.push_back(i + '0');
    }
  }

  if (a.size() >= 5) {
    cout << 0 << endl;
    return 0;
  }

  for (char i = '0'; i <= '9'; i++) {
    for (char j = '0'; j <= '9'; j++) {
      for (char k = '0'; k <= '9'; k++) {
        for (char l = '0'; l <= '9'; l++) {
          bool t = false;

          for (auto& vi: a) {
            if ((i != vi) && (j != vi) && (k != vi) && (l != vi)) {
              t = true;
              break;
            }
          }

          for (auto& vi: b) {
            if ((i == vi) || (j == vi) || (k == vi) || (l == vi)) {
              t = true;
              break;
            }
          }

          if (t) {
            continue;
          }

          ans++;
        }
      }
    }
  }

  cout << ans << endl;

  return 0;
}
