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

string S;
int len;
long long ans = 0;

int main(int argc, char *argv[])
{
  cin >> S;
  len = S.size();

  for (int i = 0; i < (1 << (len-1)); i++) {
    long long num = S[0]-'0';

    for (int j = 0; j < len-1; j++) {
      if (i & (1 << j)) {
        ans += num;
        num = 0;
      }
      num = num*10 + (S[j + 1]-'0');
    }

    ans += num;
  }

  cout << ans << endl;
  return 0;
}
