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
  int d[11];
  string S;
  cin >> S;

  fill(d, d + 11, 0);
  for (int i = 0; i < S.length(); i++) {
    d[i] = (S[i] == 'A'||S[i] == 'C'||S[i] == 'G'||S[i] == 'T');
  };

  int ans = 0;
  int tmp = 0;
  for (int i = 0; i < S.length(); i++) {
    if (d[i]) {
      tmp++;
    } else {
      ans = max(ans, tmp);
      tmp = 0;
    }
  }

  ans = max(ans, tmp);
  cout << ans << endl;
  return 0;
}
