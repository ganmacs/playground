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

string M[102];
int D[102][102];

int main()
{
  int H, W;
  cin >> H >> W;

  for (int i = 0; i < H; i++) {
    cin >> M[i];
  }

  D[0][0] = (M[0][0] == '#');

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (i == 0 && j == 0) continue;

      if (j > 0) {
        if (M[i][j-1] == '.' && M[i][j] == '#') {
          D[i][j] = D[i][j-1] + 1;
        } else {
          D[i][j] = D[i][j-1];
        }
      } else {
        D[i][j] = 1e9;
      }

      if (i > 0) {
        if (M[i-1][j] == '.' && M[i][j] == '#') {
          D[i][j] = min(D[i-1][j] + 1, D[i][j]);
        } else {
          D[i][j] = min(D[i-1][j], D[i][j]);
        }
      }
    }
  }

  cout << D[H-1][W-1] << endl;
  return 0;
}
