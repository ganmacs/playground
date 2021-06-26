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

int DP[11234];

int main()
{
  int H, N;
  cin >> H >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i];
  }

  fill(DP, DP + H + 1, 1e9);
  DP[0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= H; j++) {
      int jj = min(j + A[i], H);
      DP[jj] = min(DP[jj], DP[j] + B[i]);
    }
  }

  cout << DP[H] << endl;
  return 0;
}
