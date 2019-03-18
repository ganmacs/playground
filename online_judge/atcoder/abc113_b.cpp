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

int main(int argc, char *argv[])
{
  int N, T, A, ans = -1, v;
  float kkk, minv = 1000000.0;
  cin >> N;
  cin >> T >> A;

  for (int i = 0; i < N; i++) {
    cin >> v;
    kkk = abs(float(A) - (float(T) - float(v * 0.006)));
    if (minv > kkk) {
      minv = kkk;
      ans = i + 1;
    }
  }

  printf("%d\n", ans);
}
