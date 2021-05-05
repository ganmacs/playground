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
  string S;
  int ans = 0;
  cin >> S;

  for (int i = 0; i + 3 < S.length(); i++) {
    // ZONe
    if (S[i] == 'Z' && S[i + 1] == 'O' && S[i + 2] == 'N' && S[i + 3] == 'e') {
      ans++;
    }
  }

  cout << ans << endl;
  return 0;
}
