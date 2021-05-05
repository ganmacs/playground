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
#include <numeric>

using namespace std;

int main()
{
  string S, T = "";
  cin >> S;
  deque<char> D;

  bool r = false;
  for (auto& s: S) {
    if (s == 'R') {
      r = !r;
      continue;
    } if (r) {
      D.push_front(s);
    } else {
      D.push_back(s);
    }
  };

  if (r) {
    reverse(D.begin(), D.end());
  }

  for (auto& vi: D) {
    if (T.size() >= 1 && vi == T.back()) {
      T.pop_back();
    } else {
      T.push_back(vi);
    }
  };


  cout << T << endl;
  return 0;
}
