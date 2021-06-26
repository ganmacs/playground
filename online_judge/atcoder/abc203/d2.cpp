#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int M[802][802];
int D[802][802];

int main()
{
  int N, K;
  cin >> N >> K;

  long long T = (K*K)/2 + 1;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      D[i][j] = 0;
      cin >> M[i][j];
    }
  }

  long long ng = -1, ok = 1e9;

  while (abs(ng-ok) > 1) {
    long long p = (ng + ok)/2;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        D[i][j] = D[i-1][j] + D[i][j-1] - D[i-1][j-1] + ((M[i-1][j-1] > p) ? 1 : 0);
      }
    }

    bool t = false;
    for (int i = K; i <= N; i++) {
      for (int j = K; j <= N; j++) {
        if (D[i][j] - D[i-K][j] - D[i][j-K] + D[i-K][j-K] < T) {
          t = true;
          break;
        }
      }
    }

    if (t) {
      ok = p;
    } else {
      ng = p;
    }
  }

  cout << ok << endl;

  return 0;
}
