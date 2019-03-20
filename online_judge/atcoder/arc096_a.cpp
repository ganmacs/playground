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
  int A, B, C, X, Y;
  cin >> A >> B >> C >> X >> Y;

  if (A + B > 2 * C) {
    if (X < Y) {
      if (B > 2*C) {
        printf("%d\n", 2*Y*C);
      } else {
        printf("%d\n", 2*X*C + (Y-X)*B);
      }
    } else {
      if (A > 2*C) {
        printf("%d\n", 2*X*C);
      } else {
        printf("%d\n", 2*Y*C + (X-Y)*A);
      }
    }
  } else {
    printf("%d\n", X*A + Y*B);
  }
  return 0;
}
