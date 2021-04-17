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

  int N = S.length();
  for (int i = 0; i < (N + 1); i++) {
    int ok = true;
    for (int i = 0; i < (S.length()/2); i++) {
      if (S[i] != S[S.length()-1-i]) {
        ok = false;
      }
    }

    if (ok) {
      cout << "Yes" << endl;
      return 0;
    }
    S = "0" + S;
  }

  cout << "No" << endl;


  return 0;
}
