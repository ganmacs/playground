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
  cin >> S;
  int n = 0, ans = 0;;
  for (auto& vi: S) {
    if (vi == 'A'|| vi ==  'C'||vi ==  'G'||vi == 'T') {
      n++;
    } else {
      ans = max(ans, n);
      n = 0;
    }
  }

  cout << max(n, ans) << endl;
  return 0;
}
