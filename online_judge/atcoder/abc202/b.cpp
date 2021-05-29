#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  string S;
  cin >> S;

  for (int i = 0; i < S.size(); i++) {
    if (S[i] == '6') {
      S[i] = '9';
    } else if (S[i] == '9') {
      S[i] = '6';
    }
  }

  reverse(S.begin(), S.end());
  cout << S << endl;
  return 0;
}
