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

int N = 11;

int main(int argc, char *argv[])
{
  string s;
  bool A[N];
  cin >> s;

  for (int i = 0; i < s.length(); i++) {
    A[i] = (s[i] == 'A' || s[i] == 'C' || s[i] == 'G'|| s[i] == 'T');
  }

  int r = 0;
  int ans = 0;
  for (int i = 0; i < s.length(); i++) {
    if (A[i]) {
      r++;
    } else {
      ans = max(ans, r);
      r = 0;
    }
  }

  cout << max(ans, r) << endl;

  return 0;
}
