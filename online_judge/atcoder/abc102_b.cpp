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
  int N, a;
  cin >> N;

  cin >> a;
  int minv = a , maxv = a;

  for (int i = 1; i < N; i++) {
    cin >> a;

    minv = min(minv, a);
    maxv = max(maxv, a);
  }

  printf("%d\n", maxv-minv);
}
