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

int main()
{
  long long N, M, K;
  cin >> N >> M >> K;

  for (int n = 0; n <= N; n++) {
    for (int m = 0; m <= M; m++) {
      if (K == (n*M + m*N - 2*m*n)) {
        puts("Yes");
        return 0;
      }
    }
  }

  puts("No");
  return 0;
}
