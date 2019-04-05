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

const string ttt = "atcoder";

bool in(char v) {
  for (int i = 0; i < ttt.size(); i++) {
    if (ttt[i] == v) {
      return true;
    }
  }

  return false;
}

int main(int argc, char *argv[])
{
  string s, t;

  cin >> s;
  cin >> t;

  for (int i = 0; i < s.size(); i++) {
    if (s[i] != t[i]) {
      if (!((s[i] == '@' && in(t[i])) || (t[i] == '@' && in(s[i])))) {
        cout << "You will lose" << endl;
        return 0;
      }
    }
  }

  cout << "You can win" << endl;
}
