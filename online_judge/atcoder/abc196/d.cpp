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

int H, W, A, B, ans = 0;
bool M[16][16];
bool update;

void dfs(int y, int x, int a, int b) {
  printf("%d %d %d %d\n", y, x, a, b);
  if (a == A && b == B) {
    puts("---ok---");
    ans++;
    return;
  }

  if (b >= B || a >= A) {
    return;
  }

  if (a < A) {
    if ((x + 1 < W) && !M[y][x] && !M[y][x + 1]) {
      M[y][x] = true;
      M[y][x + 1] = true;

      update = false;
      for (int i = y; i < H; i++) {
        for (int j = 0; j < W; j++) {
          if (!M[i][j]) {
            update = true;
            dfs(i, j, a + 1, b);
            break;
          }
        }
      }
      if (update) {
        if (a + 1 == A && b == B) ans++;
      }

      M[y][x] = false;
      M[y][x + 1] = false;
    }

    if ((y + 1 < H) && !M[y][x] && !M[y + 1][x]) {
      M[y][x] = true;
      M[y + 1][x] = true;

      update = false;
      for (int i = y; i < H; i++) {
        for (int j = 0; j < W; j++) {
          if (!M[i][j]) {
            update = true;
            dfs(i, j, a + 1, b);
            break;
          }
        }
      }
      if (update) {
        if (a + 1 == A && b == B) ans++;
      }

      M[y][x] = false;
      M[y + 1][x] = false;
    }
  }

  if (b < B) {
    if (!M[y][x]) {
      M[y][x] = true;

      bool update = false;
      for (int i = y; i < H; i++) {
        for (int j = 0; j < W; j++) {
          if (!M[i][j]) {
            update = true;
            dfs(i, j, a , b + 1);
            break;
          }
        }
      }
      if (update) {
        if (a == A && b + 1 == B) ans++;
      }

      M[y][x] = false;
    }
  }
}

int main()
{
  cin >> H >> W >> A >> B;
  for (int i = 0; i < 16; i++) {
    fill(M[i], M[i] + 16, false);
  }
  dfs(0, 0, 0, 0);

  cout << ans << endl;
  return 0;
}
