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
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  int N, K;
  long long int ok = 0, all = 0;
  long double ans = 0;
  vector<long long int> v;
  cin >> N >> K;

  for (int i = 1; i <= N; i++) {
    long long int k = 0, l = i;
    while (l < K) {
      l *= 2;
      k++;
    }

    ans += (1.0 / (pow(2, k) * N));
  }

  printf("%0.10Lf\n", ans);
  return 0;
}
