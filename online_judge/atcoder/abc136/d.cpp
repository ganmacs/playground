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

int C[112345];

int main()
{
  string S;
  cin >> S;
  fill(C, C + S.length(), 0);

  int lr = 0;
  int j = 0;
  for (int i = 0; i < S.length();) {
    if (S[i] == 'R') {
      auto j = i + 1;
      while (j < (S.length()-1) && S[j] == 'R') j++;
      for (int k = i; k < j; k++) {
        if ((j - k) % 2 == 0) {
          C[j]++;
        } else {
          C[j-1]++;
        }
      }

      i = j;
      lr = i-1;
    } else {
      if ((i-lr) % 2 == 0) {
        C[lr]++;
      } else {
        C[lr + 1]++;
      }
      i++;
    };
  }

  cout << C[0];
  for (int i = 1; i < S.length(); i++) {
    cout << " " << C[i];
  }
  puts("");

  return 0;
}
