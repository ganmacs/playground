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
  cin >> s;

  int ap = -1, zp = -1;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'A' && ap == -1) ap = i;
    if (s[i] == 'Z') zp = i;
  }

  printf("%d\n", zp - ap + 1);
  return 0;
}
