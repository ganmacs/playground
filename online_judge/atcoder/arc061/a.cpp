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

  string S;
  cin >> S;
  int len = S.length();
  long long ans = 0;

  for (int i = 0; i < pow(2, len-1); i++) {
    long long num = S[0]-'0';
    for (int j = 0; j < (len-1); j++) {
      if (i & (1 << j)) {
        ans += num;
        num = 0;
      }
      num = num*10 + S[j + 1]-'0';
    }

    ans += num;
  }

  cout << ans << endl;
  return 0;
}
