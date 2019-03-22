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

string s;
const string w[4] = {"dream", "dreamer", "erase", "eraser"};

int c(int p) {
  int pos = p;
  for (int i = 0; i < 4; i++) {
    if (p + w[i].size() <= s.size() && s.compare(p, w[i].size(), w[i]) == 0) {
      pos = max(p, c(p + w[i].size()));

      if (pos == s.size()) return pos;
    }
  }

  return pos;
}

int main(int argc, char *argv[])
{
  cin >> s;

  if (c(0) == s.size()) {
    puts("YES");
  } else {
    puts("NO");
  };
  return 0;
}
