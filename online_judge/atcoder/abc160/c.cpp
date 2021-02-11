#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int NN = 1000001;

int
main()
{
  int K, N;
  int A[NN];
  int B[NN];

  cin >> K >> N;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
    B[i] = 0;
  }
  A[N] = K + A[0];

  // for (int i = 0; i < N + 1; i++) {
  //   cout << B[i] << endl;
  // }

  int r = 0;
  int m = 0;

  for (int i = 1; i < N + 1 ; i++) {
    auto v = A[i] - A[i-1];
    m = max(m, v);
    r += v;
  }


  cout <<   r-m << endl;
  return 0;
}
