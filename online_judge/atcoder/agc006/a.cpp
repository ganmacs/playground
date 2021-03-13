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
  string s, t;
  cin >> N >> s >> t;

  for (int i = 0; i < N; i++) {
    bool flg = true;

    for (int j = 0; (j + i) < N; j++) {
      if (s[i + j] != t[j]) {
        flg = false;
        break;
      }
    }

    if (flg) {
      cout << (N + i) << endl;
      return 0;
    }

  }

  cout << (N * 2) << endl;
  return 0;
}
