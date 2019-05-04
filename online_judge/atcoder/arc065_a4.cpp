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

bool dfs(int p) {
  if (p == s.size()) return true;

  for (int i = 0; i < 4; i++) {
    int ws = w[i].size();
    if (s.size() - p >= ws && s.substr(p, ws) == w[i]) {
      if (dfs(p + ws)) return true;
    }
  }

  return false;
}

int main(int argc, char *argv[])
{
  cin >> s;

  if (dfs(0)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}
