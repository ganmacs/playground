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
  int N, Y, v;
  cin >> N >> Y;

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j + i <= N; j++) {
      v = 10000*i + 5000*j + 1000*(N-i-j);

      if (v == Y) {
        printf("%d %d %d\n", i, j, (N-i-j));
        return 0;
      }
    }
  }
  printf("-1 -1 -1\n");
  return 0;
}
