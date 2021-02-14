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

int main(int argc, char *argv[])
{
  string S;
  cin >> S;

  long long int ans = 0;
  long long int j = 0;

  for (int i = 0; i < S.size(); i++) {
    if (S[i] == 'W') {
      ans += j;
    } else {
      j++;
    }
  }

  cout << ans << endl;

  return 0;
}
