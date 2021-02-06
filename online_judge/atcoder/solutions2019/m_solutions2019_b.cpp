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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  string s;
  int a = 0;
  cin >> s;

  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'o') {
      a++;
    }
  }

  int rest = (15 - s.size());

  if (a + rest >= 8) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
