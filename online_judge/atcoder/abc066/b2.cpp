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

  S = S.substr(0, S.length()-1);

  if (S.length() % 2 == 1) {
    S = S.substr(0, S.length()-1);
  }

  while (S.length() >= 2) {
    auto v = S.length()/2;
    auto ok = true;
    for (int i = 0; i < v; i++) {
      if (S[i] != S[i + v]) {
        ok = false;
        break;
      }
    }

    if (ok) {
      cout << S.length() << endl;
      return 0;
    }

    S = S.substr(0, S.length()-2);
  }

  return 0;
}
