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
  int N;
  int X[NN];
  int R[NN];

  cin >> N;

  for (int i = 0; i < NN; i++) {
    R[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    cin >> X[i];

    for (int p = 1; p <= 100; p++) {
      R[p] += ((X[i]-p)*(X[i]-p));
    }
  }

  int r = 10000000;

  for (int p = 1; p <= 100; p++) {
    r = min(R[p], r);
  }

  cout << r << endl;
}
