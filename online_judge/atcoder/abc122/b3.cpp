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
  int N = S.length(), ans = 0;;

  for (int i = 0; i < N; i++) {
    int a = 0;
    for (int j = 0; j + i < N; j++) {
      if (S[j + i] == 'A' || S[j + i] == 'C' || S[j + i] == 'G' || S[j + i] == 'T') {
        a++;
      } else {
        break;
      }
    }

    ans = max(a, ans);
  }

  cout << ans << endl;

  return 0;
}
