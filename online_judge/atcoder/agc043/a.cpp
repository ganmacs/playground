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
#include <numeric>

using namespace std;

int M[200][200];

int main()
{
  int H, W;
  cin >> H >> W;
  vector<string> V(H);

  for (auto& vi: V) {
    cin >> vi;
  };

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (i == 0 && j == 0) {
        M[i][j] = (V[i][j] == '#' ? 1 : 0);
        continue;
      }

      if (j > 0) {
        M[i][j] = ((V[i][j] == '#' && V[i][j-1] == '.') ? 1 : 0) + M[i][j-1];
      } else {
        M[i][j] = 1e9;
      }

      if (i > 0) {
        M[i][j] = min(M[i][j], ((V[i][j] == '#' && V[i-1][j] == '.') ? 1 : 0) + M[i-1][j]);
      }
    }
  }

  cout << M[H-1][W-1] << endl;
  return 0;
}
