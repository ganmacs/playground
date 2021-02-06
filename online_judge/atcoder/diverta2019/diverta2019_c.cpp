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
  int N, ans = 0, a = 0, b = 0, ab = 0;
  string s[20000];
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> s[i];
  }

  for (int i = 0; i < N; i++) {
    std::string::size_type pos = s[i].find("AB");
    while (pos != std::string::npos) {
      ans++;
      pos = s[i].find("AB", pos + 2);
    }

    if (s[i].front() == 'B' && s[i].back() == 'A') {
      ab++;
    } else if (s[i].front() == 'B') {
      b++;
    } else if (s[i].back() == 'A') {
      a++;
    }
  }

  int tmp = ans + max(ab - 1, 0);
  if (ab > 0) {
    if (a >= 1) {
      tmp++;
      a--;
    }

    if (b >= 1) {
      tmp++;
      b--;
    }
  }

  tmp += min(a, b);

  cout << tmp << endl;
  return 0;
}
