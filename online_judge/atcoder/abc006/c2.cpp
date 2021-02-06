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

int main(int argc, char *argv[]) {
  int N, M;
  cin >> N >> M;

  for (int b = 0; b < N; b++) {
    if ((4*N - M - b) % 2 != 0) continue;
    if ((M- 2*N -b) % 2 != 0) continue;

    int a = (4*N - M - b) / 2;
    int c = (M - 2*N -b) / 2;

    if (c >= 0 && a >= 0 && a + b + c == N && 2*a + 3*b + 4*c == M) {
      cout << a << " " << b << " " << c << endl;
      return 0;
    }
  }

  cout << -1 << " " << -1 << " " << -1 << endl;
  return 0;
}
