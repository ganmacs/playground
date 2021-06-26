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
  int ans = 0;

  int i = 0, j = S.size()-1;
  while (i < j) {
    if (S[i] == S[j]) {
      i++; j--;
    } else if (S[i] == 'x') {
      i++;
      ans++;
    } else if (S[j] == 'x') {
      j--;
      ans++;
    } else {
      printf("%d\n", -1);
      return 0;
    }
  }

  printf("%d\n", ans);
  return 0;
}
