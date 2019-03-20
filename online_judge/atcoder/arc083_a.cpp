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
  int A, B, C, D, E, F, aa = 0, bb = 0, tw, ts;
  float maxv = 0.0;
  cin >> A >> B >> C >> D >> E >> F;

  for (int a = 0; a <= F; a += (100*A)) {
    for (int b = 0; b + a <= F; b += (100*B)) {
      tw = a + b;
      if (tw > 0) {
        for (int c = 0; c + tw <= F; c += C) {
          for (int d = 0; c + d + tw <= F; d += D) {
            ts = c + d;
            if (ts * 100 <= E * tw) {
              float v = (100.0 * ts) / (ts + tw + 0.0);
              if (maxv <= v) {
                aa = ts + tw;
                bb = ts;
                maxv = v;
              }
            }
          }
        }
      }
    }
  }
  printf("%d %d\n", aa, bb);
  return 0;
}
