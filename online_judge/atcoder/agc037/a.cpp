#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int
main()
{
  int ans = 1;
  string S;
  string a = "", b = "";
  cin >> S;

  a = S[0];
  for (int i = 1; i < S.length(); i++) {
    b += S[i];
    if (a != b) {
      a = b;
      b = "";
      ans++;
    }
  }

  cout <<  ans << endl;
  return 0;
}
