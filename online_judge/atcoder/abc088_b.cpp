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
  int N, c[1000], a = 0, b = 0;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> c[i];

  sort(c, c + N);

  for (int i = 0; i < N; i++) {
    if (i%2 == 0) {
      a += c[i];
    } else {
      b += c[i];
    }
  }
  printf("%d\n", abs(a-b));
}
