#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  unsigned long long N, K;
  cin >> N >> K;

  if (K == 1) {
    printf("1 1 1\n");
    return 0;
  }

  K -= 1;
  cout << K << endl;

  unsigned long long t = K/7;
  cout << t << endl;

  int t2 = K%7;
  printf("%d\n", t2);

  unsigned long long a[8][3] = {
                                { 0, 0, 0 },
                                { 0, 0, 1 },
                                { 0, 1, 0 },
                                { 1, 0, 0 },
                                { 0, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 0 },
                                { 1, 1, 1 },
  };

  printf("%llu %llu %llu\n", 1 + t + a[t2][0], 1 + t + a[t2][1], 1 + t + a[t2][2]);

  return 0;
}
