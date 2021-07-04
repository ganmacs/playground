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
  int N, H;
  cin >> H >> N;
  vector<long long> A(N), B(N), C(H + 1, 1e18);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i];
  }

  C[0] = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 1; j <= H; j++) {
      C[j] =  min(C[j], C[max(0LL, j-A[i])] + B[i]);
    }
  }

  cout << C[H] << endl;
  return 0;
}
