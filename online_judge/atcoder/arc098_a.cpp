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
  int N;
  string S;
  int e[500000], er[500000], w[500000], wr[500000];
  cin >> N;
  cin >> S;
  e[0] = er[0] = w[0] = wr[0] = 0;
  e[N + 1] = er[N + 1] = w[N + 1] = wr[N + 1] = 0;

  for (int i = 1; i <= N; i++) {
    if (S[i-1] == 'W') {
      w[i] = w[i-1] + 1;
      e[i] = e[i-1];
    } else {
      e[i] = e[i-1] + 1;
      w[i] = w[i-1];
    }
  }

  int minv = 5432100;
  for (int i = 1; i <= N; i++) {
    minv = min(minv, w[i-1] + (e[N]-e[i]));
  }

  cout << minv << endl;
  return 0;
}
