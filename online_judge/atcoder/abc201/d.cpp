#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int H, W;
char A[2001][2001];
bool visited[2001][2001];
vector<vector<int>> dp(2001, vector<int>(2001, -1));

int dfs(int i, int j)
{
  if (visited[i][j]) {
    return dp[i][j];
  }

  int ret = 0;
  if ((i + j) % 2 == 0) {
    ret = -1e9;

    if (i + 1 < H) {
      ret = max(ret, dfs(i + 1, j) + (A[i + 1][j] == '+' ? 1 : -1));
    }

    if (j + 1 < W) {
      ret = max(ret, dfs(i, j + 1) + (A[i][j + 1] == '+' ? 1 : -1));
    }
  } else {
    ret = 1e9;

    if (i + 1 < H) {
      ret = min(ret, dfs(i + 1, j) + (A[i + 1][j] == '+' ? -1 : 1));
    }

    if (j + 1 < W) {
      ret = min(ret, dfs(i, j + 1) + (A[i][j + 1] == '+' ? -1 : 1));
    }
  }

  visited[i][j] = true;
  return dp[i][j] = ret;
}

int main()
{
  cin >> H >> W;

  for (int i = 0; i < H; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < W; j++) {
      A[i][j] = s[j];
      visited[i][j] = false;
    }
  }

  dp[H-1][W-1] = 0;
  visited[H - 1][W - 1] = true;
  auto ans = dfs(0, 0);
  if (ans == 0) {
    cout << "Draw\n";
  } else if (ans > 0) {
    cout << "Takahashi\n";
  } else {
    cout << "Aoki\n";
  }
  return 0;
}
