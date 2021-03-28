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
  int N;
  cin >> N;
  vector< long long int> V(N);

  for (int i = 0; i < N; i++) {
    cin >> V[i];
  }


  long long int ans = 1e18;
  for (int i = 0; i < (1 << (N-1)); i++) {
    long long oor = 0;
    long long xoor = 0;
    for (int j = 0; j <= N; j++) {
      if (j < N) {
        oor |= V[j];
      }

      if (j == N || i & 1 << j) {
        xoor ^= oor;
        oor = 0;
      }
    }

    ans = min(ans, xoor);
  }


  cout << ans << endl;
  return 0;
}
