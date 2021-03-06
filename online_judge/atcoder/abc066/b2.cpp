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

  while (S.size() >= 0) {
    S.pop_back();
    if (S.size() % 2 == 1) {
      S.pop_back();
    }

    if (S.substr(0, S.size()/2) == S.substr(S.size()/2, S.size()/2)) {
      cout << S.size() << endl;
      return 0;
    }
  }

  return 0;
}
