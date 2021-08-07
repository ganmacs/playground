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

const int L = 1000000007;

int main()
{
  int N;
  cin >> N;
  string S1, S2;
  cin >> S1 >> S2;

  long long ans = 0;
  int prev, i;

  if (S1[0] == S2[0]) {
    ans = 3;
    prev = 1;
    i = 1;
  } else {
    ans = 6;
    prev = 2;
    i = 2;
  }

  while (i < N) {
    if (S1[i] == S2[i]) {
      if (prev == 1) {          // 1 -> 1
        ans = (ans*2)%L;
      } else {                  // 2 -> 1
        // nothing
      }
      prev = 1;
      i++;
    } else {
      if (prev == 1) {          // 1->2
        ans = (ans*2)%L;
      } else {                  // 2->2
        ans = (ans*3)%L;
      }
      prev = 2;
      i += 2;
    }
  }

  printf("%lld\n", ans);

  return 0;
}
