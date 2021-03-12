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
  int N, M, s;
  map<int, char> m;
  char c;
  cin >> N >> M;

  bool f = true;

  string sss = "";
  for (int i = 0; i < N; i++) {
    sss += "0";
  }

  for (int i = 0; i < M; i++) {
    cin >> s >> c;
    if (m.find(s) != m.end() && m[s] != c) {
      f = false;
      break;
    }
    m[s] = c;
  }

  if (!f) {
    cout << -1 << endl;
    return 0;
  }

  for (const auto &mi: m) {
    sss[mi.first-1] = mi.second;
  }

  if (sss.size() != 1 && sss[0] == '0') {
    if (m[1] == '0') {
      cout << -1 << endl;
      return 0;
    } else {
      sss[0] = '1';
    }
  }

  cout << sss << endl;
  return 0;
}
