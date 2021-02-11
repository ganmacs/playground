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
  int N, M, X;
  int A[NN];
  int B[NN];

  cin >> N >> M >> X;

  for (int i = 0; i < N + 1; i++) {
    B[i] = 0;
  }

  for (int i = 0; i < M; i++) {
    cin >> A[i];
    B[A[i]] = 1;
  }

  for (int i = 0; i < N + 1; i++) {
    B[i] = B[i] + B[i-1];
  }



  cout<< min(B[N]-B[X], B[X]-B[0]) << endl;

  return 0;
}
