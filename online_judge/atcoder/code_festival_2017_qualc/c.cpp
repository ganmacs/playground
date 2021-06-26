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

  map<char, int> M;
  for (auto& vi: S) M[vi]++;

  if (S.size() == 1) {
    cout << 0 << endl;
    return 0;
  }

  int l = 0, r = N-1;
  int ans = 0;
  while (r - l >= 1) {
    if (S[l] == S[r]) {
      l++; r--;
    } else if (S[l] == 'x') {
      ans++;
      l++;
    } else if (S[r] == 'x') {
      ans++;
      r--;
    } else {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << ans << endl;

  return 0;
}
