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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  int N, a[300000], b[300000];
  string S;
  cin >> N;
  cin >> S;


  a[0] = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == '#') {
      a[i+1] = a[i] + 1;
    } else {
      a[i+1] = a[i];
    }
  }

  b[N] = 0;
  for (int i = N-1; i >= 0; i--) {
    if (S[i] == '.') {
      b[i] = b[i + 1] + 1;
    } else {
      b[i] = b[i + 1];
    }
  }


  int ans = N + 1;
  for (int i = 0; i <= N; i++) {
    ans = min(ans, a[i] + b[i]);
  }

  cout << ans << endl;
  return 0;
}
