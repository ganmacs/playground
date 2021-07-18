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
  cin >> S;
  int N = S.size();
  long long ans = 0;

  long long num = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'A') {
      num++;
    } else if (i + 1 < N && S[i] == 'B' && S[i + 1] == 'C') {
      ans += num;
      i++;
    } else {
      num = 0;
    }
  }

  cout << ans << endl;
  return 0;
}
