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
  string S;
  int N;
  cin >> N >> S;

  int l = 0;
  string ans = "";
  for (auto& vi: S) {
    ans += vi;
    if (vi == '(') {
      l++;
    } else {
      if (l == 0) {
        ans = "(" + ans;
      } else {
        l--;
      }
    }
  }

  for (int i = 0; i < l; i++) ans += ")";
  cout << ans << endl;
  return 0;
}
