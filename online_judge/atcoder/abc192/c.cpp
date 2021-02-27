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
int VVV[10000];

long long int f(long long int v) {
  auto N = 0;
  while (v != 0) {
    VVV[N] = (v % 10);
    N++;
    v /= 10;
  }

  sort(VVV, VVV + N);

  auto b = 1;
  long long int g1 = 0, g2 = 0;
  for (int i = 0; i < N; i++) {
    g1 +=  VVV[i] * b;
    b *= 10;
  }

  sort(VVV, VVV + N, greater<int>());
  b = 1;
  for (int i = 0; i < N; i++) {
    g2 += VVV[i] * b;
    b *= 10;
  }

  return g1 - g2;
}

int main(int argc, char *argv[])
{
  long long int N, K;
  cin >> N >> K;

  for (int i = 0; i < K; i++) {
    N = f(N);

    if (N == 0) {
      break;
    }
  }

  cout << N << endl;

  return 0;
}
