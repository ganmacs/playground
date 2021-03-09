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

  int ans = 0;
  for (int i = 0; i < S.length(); i++) {
    auto aaa = 0;
    for (int j = i; j < S.length(); j++) {
      if (S[j] == 'A' || S[j] == 'G' || S[j] == 'C' || S[j] == 'T') {
        aaa++;
      } else {
        break;
      }
    }

    ans = max(ans, aaa);
  }

  cout << ans << endl;
  return 0;
}
