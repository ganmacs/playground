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
  int N, M, a;
  cin >> N >> M;
  vector<long long> V(N + 1, 0), A(N + 1, 0);
  for (int i = 0; i < M; i++) {
    cin >> a;
    V[a] = 1;
  }

  A[0] = 1;

  for (int i = 1; i <= N; i++) {
    if (V[i] == 1 && V[i-1] == 1) {
      cout << 0 << endl;
      return 0;
    }

    if (V[i] == 1) continue;

    if (i - 2 >= 0 && V[i-2] == 0) {
      A[i] = A[i-2];
    }

    if (V[i-1] == 0) {
      A[i] += A[i-1];
    }

    A[i] %= 1000000007;
  }

  cout << A[N] << endl;
  return 0;
}
