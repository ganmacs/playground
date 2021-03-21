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
#include <list>

using namespace std;

int main()
{
  list<char> L;
  int c0 = 0, c1 = 0;
  string S;
  cin >> S;
  for (int i = 0; i < S.length(); i++) {
    if (S[i] == '0') {
      c0++;
    } else {
      c1++;
    }
  }

  cout << 2*min(c0, c1) << endl;

  return 0;
}
