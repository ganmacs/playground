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

string s;

long long S[100010];

int main(int argc, char *argv[])
{

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> S[i];

  long long ans1 = 0, ans2 = 0, sum = 0;
  // S[0] > 0
  for (int i = 0, s = 1; i < N; i++, s *= -1) {
    sum += S[i];
    if (sum*s <= 0) {
      ans1 += abs(sum-s);
      sum = s;
    }
  }

  sum = 0;
  // S[0] < 0
  for (int i = 0, s = -1; i < N; i++, s *= -1) {
    sum += S[i];
    if (sum*s <= 0) {
      ans2 += abs(sum-s);
      sum = s;
    }
  }

  printf("%lld\n", min(ans1, ans2));
}
