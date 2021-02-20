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
  // long long int ll[543210], lr[543210];
   int ll[543210], lr[543210];
  cin >> S;

  ll[0] = 0;
  lr[S.length()] = 0;

  auto len = S.length();

  for (int i = 0; i < len; i++) {
    if (S[i] == '<') {
      ll[i + 1] = ll[i] + 1;
    } else {
      ll[i + 1] = 0;
    }

    if (S[len - i - 1] == '>') {
      lr[len - i - 1] = lr[len - i] + 1;
    } else {
      lr[len - i - 1] = 0;
    }
  }


  auto j = 0;
  for (int i = 0; i <= len; i++) {
    auto v = max(ll[i], lr[i]);
    j += v;
  }

  cout << j << endl;

  return 0;
}
