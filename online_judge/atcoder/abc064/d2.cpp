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
  int N, ll = 0;
  string S;
  cin >> N >> S;

  string l = "";
  for (auto& vi: S) {
    if (vi == '(') {
      ll++;
    } else {
      if (ll == 0) {
        l += "(";
      } else {
        ll--;
      }
    }
  }

  string r = "";
  for (int i = 0; i < ll; i++) {
    r += ")";
  }

  cout << l << S << r << endl;
  return 0;
}
