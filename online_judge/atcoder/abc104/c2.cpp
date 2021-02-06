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
  int D, G;
  cin >> D >> G;

  vector<int> p(D + 10), c(D + 10);
  for (int i = 0; i < D; i++) {
    cin >> p[i] >> c[i];
  }

  int minv = 1e7;
  for (int i = 0; i < (1 << D); i++) {
    int sum = 0, cnt = 0;

    for (int j = 0; j < D; j++) {
      if (i & (1 << j)) {
        sum += p[j] * (j + 1) * 100 + c[j];
        cnt += p[j];
      }
    }
    for (int j = D-1; j >= 0; j--) {
      if (i & (1 << j)) continue;
      int cont = 0;

      while ((cont + 1) < p[j] && sum < G) {
        sum += (j + 1)*100;
        cnt++;
        cont++;
      }
    }

    if (sum >= G) {
      minv = min(minv, cnt);
    }
  }

  cout << minv << endl;
}
