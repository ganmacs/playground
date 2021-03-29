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
  cin >> S;

  vector<int> res(S.length(), 0);
  vector<int> V;
  V.push_back(0);
  for (int i = 0; i < S.length();) {
    int j = i;
    while (j < S.length() && S[j] == S[i]) j++;
    V.push_back(j);

    auto size = V.size();
    if (S[i] == 'L') {
      auto lll = V[size-1] - V[size-2];
      auto rrr = V[size-2] - V[size-3];
      res[i-1] = (rrr + 1)/2 + lll/2;
      res[i] = (lll + 1)/2 + rrr/2;
    }
    i = j;
  }

  for (auto& vi: res) {
    cout << vi << " ";
  };
  puts("");

  return 0;
}
