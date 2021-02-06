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

  int A, B, C, X, ans;
  cin >> A >> B >> C >> X;
  for (int i = 0; i <= A; i++) {
    for (int j = 0; j <= B; j++) {
      for (int l = 0; l <= C; l++) {
        if (((500 * i) + (100 * j) + (50 * l)) == X) ans++;
      }
    }
  }

  printf("%d\n", ans);
}
