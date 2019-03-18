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

const int MAX = 100000;

long long int A[300];

int main(int argc, char *argv[])
{

  int N;
  cin >> N;

  long long int m = 100000000;

  for (int i = 0; i < N; i++) {
    long long int v = 0, a = 0;
    cin >> a;
    while ((a & 1) != 1 && a != 0) {
      v++;
      a = (a >> 1);
    }
    m = min(m, v);

    if (m == 0) {
      printf("%lld\n", m);
      return 0;
    }
  }

  printf("%lld\n", m);
  return 0;
}
