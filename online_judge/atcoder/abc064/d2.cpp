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
  string S;
  cin >> N >> S;

  string l;

  int t = 0;
  for (auto& vi: S) {
    if (vi == '(') {
      t++;
    } else {
      if (t == 0) {
        l += "(";
      } else {
        t--;
      }
    }
  }

  for (int i = 0; i < t; i++) S += ")";

  cout << l + S << endl;
  return 0;
}
