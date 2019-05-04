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

const int INF = 1e9;


int main(int argc, char *argv[])
{
  int H, W, N, sx, sy;
  string S, T;
  int sl = 0, sr = 0, su = 0, sd = 0, tl = 0, tu = 0, td = 0, tr = 0;
  cin >> H >> W >> N;
  cin >> sy >> sx;
  cin >> S;
  cin >> T;
  int midx = W/2, midy = H/2;

  bool found = false;

  for (int i = 0; i < N; i++) {
    if (S[i] == 'D') { sd++; }
    else if (S[i] == 'U') { su++; }
    else if (S[i] == 'L') { sl++; }
    else if (S[i] == 'R') { sr++; }

    if (W < sx + sr) {
      found = true;
    } else if (0 >= sx - sl) {
      found = true;
    } else if (H < sy + sd) {
      found = true;
    } else if (0 >= sy - su) {
      found = true;
    }

    if (found) break;

    if (T[i] == 'D') {
      if (sy - su < midy) su--;
    } else if (T[i] == 'U') {
      if (sy + sd > midy) sd--;
    } else if (T[i] == 'L') {
      if (sx + sr > midx) sr--;
    } else if (T[i] == 'R') {
      if (sx - sl < midx) sl--;
    }
  }

  if (found) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }

  return 0;
}
