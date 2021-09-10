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
  int H, N, a, b;
  cin >> H >> N;
  vector<long long> M(H + 1, 1e18);
  M[0] = 0;

  for (int i = 0; i < N; i++) {
    cin >> a >> b;

    for (int j = a; j <= H; j++) {
      M[j] = min(M[j], M[j-a] + b);
    }

    for (int j = 0; j <= a; j++) {
      M[H] = min(M[H], M[H-j] + b);
    }
  }

  printf("%lld\n", M[H]);
  return 0;
}
