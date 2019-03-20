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

int digi(long long int v) {
  int i = 0;
  while (v > 0) {
    v /= 10;
    i++;
  }
  return i;
}

int main(int argc, char *argv[])
{
  long long int N;
  int minv = 100;
  cin >> N;

  for (long long int i = 1; i <= sqrt(N); i++) {
    if (N % i == 0) {
      minv = min(minv, min(digi(N), digi(N/i)));
    }
  }

  printf("%d\n", minv);

  return 0;
}
