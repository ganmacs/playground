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
  int N;
  string s[200];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> s[i];
  }

  for (int i = 0; i < N; i++) {
    int p = 0, ans = 0, l = s[i].size();
    while (p < l) {
      auto pos1 = s[i].find("tokyo", p);
      auto pos2 = s[i].find("kyoto", p);

      if (pos2 == string::npos && pos1 == string::npos) {
        break;
      } else if (pos1 == string::npos) {
        p = pos2;
      } else if (pos2 == string::npos) {
        p = pos1;
      } else if (pos1 < pos2) {
        p = pos1;
      } else {
        p = pos2;
      }
      p += 5;                   // length of string
      ans++;
    }

    cout << ans << endl;
  }

  return 0;
}
