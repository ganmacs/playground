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

int a[200000], b[200000], c[200000];

int main(int argc, char *argv[])
{
  int N;

  cin >> N;

  b[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    b[i + 1] = max(b[i], a[i]);
  }

  c[N] = 0;
  for (int i = N-1; i >= 0; i--) {
    c[i-1] = max(c[i], a[i]);
  }

  for (int i = 0; i < N; i++) {
    cout << max(b[i], c[i]) << endl;
  }

  return 0;
}
