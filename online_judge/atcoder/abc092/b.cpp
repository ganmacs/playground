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

int NN = 200;

int main(int argc, char *argv[])
{
  int N, D, X, r = 0, r1 = 0;
  int A[NN];

  cin >> N;
  cin >> D >> X;

  r += X;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
    r += ((D - 1)/A[i]) + 1;
  }

  cout << r << endl;
  return 0;
}
