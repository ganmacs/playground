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
#include <numeric>

using namespace std;

int main()
{
  string s;
  cin >> s;
  int N = s.length();
  int d[3] = {0, 0, 0};
  for (int i = 0; i < N; i++) {
    d[s[i]-'a']++;
  }

  auto m1 = min(d[0], min(d[1], d[2]));
  for (int i = 0; i < 3; i++) {
    d[i] -= m1;
  }
  cout << (max(d[1],  max(d[0], d[2])) <= 1 ? "YES" : "NO") << endl;

  return 0;
}
