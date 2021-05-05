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
  unsigned long long int K;
  string S;
  cin >> S >> K;

  int N = S.length();
  unsigned long long ans = 0;

  vector<int> LI;
  for (int i = 0; i < S.length();) {
    int j = i;
    while (j < S.length() && S[j] == S[i]) {
      j++;
    }
    LI.push_back(j-i);
    ans += ((j-i)/2);
    i = j;
  }
  ans *= K;

  if (LI.size() == 1) {
    ans = (K*LI[0])/2;
  } else if (S.length() >= 2 && (S[0] == S[S.length()-1])) {
    if ((LI[0] + LI[LI.size()-1]) % 2 == 0) {
      ans += (K-1);
    }
  }

  cout << ans << endl;
  return 0;
}
// aaa/aa
// aaa/ab
