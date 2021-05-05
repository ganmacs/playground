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

string aaa[10] = { "ACH", "ACM", "ACR",
                   "AHM", "AHR", "AMR",
                   "CHM", "CHR", "CMR", "HMR" };

int main()
{
  int N;
  vector<string> V;
  string s;
  map<char, int> M;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> s;
    if (s[0] == 'M' || s[0] == 'A' || s[0] == 'R' || s[0] == 'C' || s[0] == 'H') {
      V.push_back(s);
      M[s[0]]++;
    }
  }

  if (V.size() < 3) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long int ans = 0;

  for (int i = 0; i < 10; i++) {
    unsigned long long int tans = 1;
    for (int j = 0; j < 3; j++) {
      tans *= M[aaa[i][j]];
    }
    ans += tans;
  }

  cout << ans << endl;
  return 0;
}
