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

int main(int argc, char *argv[])
{
  cin >> s;

  int i = s.size();
  while (i >= 0) {
    int ok = false;

    for (int j = 0; j < 4; j++) {
      if (int(i - w[j].size()) >= 0 && s.compare(i - w[j].size(), w[j].size(), w[j]) == 0) {
        ok = true;
        i -= w[j].size();
      }
    }
    if (!ok) break;
  }

  if (i == 0) {
    puts("YES");
  } else {
    puts("NO");
  };

  return 0;
}
