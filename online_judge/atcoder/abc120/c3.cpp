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
  int a = 0, b = 0;
  string S;
  cin >> S;

  for (int i = 0; i < S.length(); i++) {
    if (S[i] == '0') {
      a++;
    } else {
      b++;
    }
  }

  cout << (S.length()-abs(a-b)) << endl;
  return 0;
}
