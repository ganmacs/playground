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
  int K;
  cin >> S >> K;

  for (int i = 0; i < S.size() && K; i++) {
    int d = S[i] - 'a';
    if (d != 0) {
      int dd = 26 - d;
      if (K >= dd) {
        K -= dd;
        S[i] = 'a';
      }
    }
  }

  if (K) {
    S[S.size()-1] = S.back() + (K % 26);
  }

  cout << S << endl;
  return 0;
}
