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
  int p[123456], c[123456], pi[123456], mask[123456];

  cin >> D >> G;

  int sum = 0;
  for (int i = 0; i < D; i++) {
    cin >> p[i] >> c[i];
    mask[i] = (1 << p[i])-1;

    for (int j = 0; j < p[i]; j++) {
      pi[sum + j] = i;
    }
    sum += p[i];
  }

  int minv = 1e8;
  for (int i = 0; i < (1 << sum); i++) {
    int vv = 0, vvv = 0;
    for (int j = 0; j < sum; j++) {
      if (i & (1 << j)) {
        int t = pi[j];
        vv += (t + 1)*100;
        vvv++;
      }
    }

    for (int j = 0; j < D; j++) {
      if ((i&mask[j]) == mask[j]) {
        // printf("%d\n", pi[j]);
        printf("%d %d\n", j, c[pi[j]]);
        vvv += c[pi[j]];
      }
    }

    if (vv >= G) {
      minv = min(minv, vvv);
    }

  }

  printf("%d\n", minv);

}
