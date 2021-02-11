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

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  sort(A, A + N);
  auto v = A[N/2] - A[(N/2)-1];

  cout <<   v<< endl;
  return 0;
}
