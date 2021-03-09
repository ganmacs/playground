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
  string s;
  int ans = 1;
  cin >> s;

  while (s.length() > 0) {
    s = s.substr(0, s.length() - 1);
    if (s.length() % 2 == 1) {
      s = s.substr(0, s.length() - 1);
    }

    int len = s.length();
    if (s.substr(0, len/2) == s.substr(len/2, len/2)) {
      cout << len << endl;
      break;
    };
  }

  return 0;
}
