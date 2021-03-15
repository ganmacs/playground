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

int main()
{
  string S;
  long long ans = 0;
  cin >> S;

  for (int i = 0; i < pow(2, S.length()-1); i++) {
    long long int v = 0;

    for (int j = 0; j < S.length()-1; j++) {
      v += S[j] - '0';

      if ((i >> j) & 1) {
        ans += v;
        v = 0;
      } else {
        v *= 10;
      }
    }

    ans += (v*10 + S[S.length()-1]-'0');
  }

  cout << ans << endl;

  return 0;
}
