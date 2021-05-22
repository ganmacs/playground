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

int main()
{
  long long int Q, H, S, D, N;
  cin >> Q >> H >> S >> D >> N;
  Q *= 4;
  H *= 2;
  long long v = min(Q, min(H, S));

  if (v*2 <= D) {
    cout << v*N << endl;
  } else {
    cout << (D*(N/2) + (N % 2)*v) << endl;
  }

  return 0;
}
