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
  int N = S.size();

  long long int ans = 0;

  for (int i = 0; i < N;) {
    int j = i;
    if (S[j] == '<') {
      while (S[i] == S[j] && j < N) j++;
    }

    int t = j;
    if (S[t] == '>') {
      while (S[j] == S[t] && t < N) t++;
    }

    ans += max((j-i), (t-j));
    for (int k = 1; k < (j-i); k++) ans += k;
    for (int k = 1; k < (t-j); k++) ans += k;
    i = t;
  }

  cout << ans << endl;
  return 0;
}
