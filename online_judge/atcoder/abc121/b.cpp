
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

  int N, M, C;

  int A[NN][NN];
  int B[NN];
  cin >> N >> M >> C;

  for (int j = 0; j < M; j++) {
    cin >> B[j];
  }


  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> A[i][j];
    }
  }

  int r = 0;
  int t = 0;

  for (int i = 0; i < N; i++) {
    t = C;
    for (int j = 0; j < M; j++) {
      t += A[i][j] * B[j];
    }

    if (t>0) {
      r++;
    }
  }

  cout << r << endl;
}
