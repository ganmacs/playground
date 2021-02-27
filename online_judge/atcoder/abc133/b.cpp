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


int X[30][30];

int main(int argc, char *argv[])
{
  int N, D, ans = 0;
  cin >> N >> D;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) {
      cin >> X[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      long long int x = 0;
      for (int k = 0; k < D; k++) {
        x += pow(X[i][k]-X[j][k], 2);
      }

      double v = sqrt(x);
      long long int v2 = v;
      if (v2 == v) {
        ans++;
      }
    }
  }

  cout << ans << endl;
  return 0;
}
