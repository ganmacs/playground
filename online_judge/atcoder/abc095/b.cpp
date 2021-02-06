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
  int N, X, minv = 1000000, a, sum = 0;
  cin >> N >> X;

  for (int i = 0; i < N; i++) {
    cin >> a;
    sum += a;
    minv = min(a, minv);
  }

  printf("%d\n", N + ((X - sum) / minv));
}
