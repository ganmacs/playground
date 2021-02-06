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
  int A, B, K, a, b;
  cin >> A >> B >> K;

  int N[102];

  if (A>B) {
    a = A;
    b = B;
  } else {
    a = B;
    b = A;
  }

  int kk = 0;

  for (int i = 1; i <= b/2; i++) {
    if (A%i == 0 && B%i == 0) {
      kk++;
      N[kk] = i;
    }
  }

  if (a%b == 0) {
    kk++;
    N[kk] = b;
  }

  cout << N[kk-K + 1] << endl;
}
