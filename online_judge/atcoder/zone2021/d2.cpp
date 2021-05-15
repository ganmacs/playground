#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <numeric>

using namespace std;


int main()
{
  deque<char> Q;
  bool r = false;
  string S;
  cin >> S;

  for (auto& vi: S) {
    if (vi == 'R') {
      r = !r;
    } else {
      if (r) {
        Q.push_front(vi);
      } else {
        Q.push_back(vi);
      }
    }
  };

  if (r) {
    reverse(Q.begin(), Q.end());
  }

  string ans = "";
  for (auto& vi: Q) {
    if (ans.size() == 0) {
      ans += vi;
      continue;
    }

    if (ans.back() == vi) {
      ans.pop_back();
    } else {
      ans += vi;
    }
  };

  cout << ans << endl;
  return 0;
}
