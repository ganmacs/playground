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

int dp[2001][2001];
vector<vector<bool>> visited(2001, vector<bool>(2001, false));
char A[2001][2001];

int dfs(int i, int j)
{
  if (visited[i][j]) {
    return dp[i][j];
  }
  visited[i][j] = true;

  int ret;
  if ((i + j) % 2 == 0) {
    ret = -1e9;
    if (i + 1 < H) ret = max(ret, dfs(i + 1, j) + (A[i + 1][j] == '+' ? 1 : -1));
    if (j + 1 < W) ret = max(ret, dfs(i, j + 1) + (A[i][j + 1] == '+' ? 1 : -1));
  } else {
    ret = 1e9;
    if (i + 1 < H) ret = min(ret, dfs(i + 1, j) - (A[i + 1][j] == '+' ? 1 : -1));
    if (j + 1 < W) ret = min(ret, dfs(i, j + 1) - (A[i][j + 1] == '+' ? 1 : -1));
  }

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
    }
  }

  visited[H-1][W-1] = true;
  dp[H-1][W-1] = 0;

  auto r = dfs(0, 0);
  if (r == 0) {
    cout << "Draw" << endl;
  } else if (r > 0) {
    cout << "Takahashi" << endl;
  } else {
    cout << "Aoki" << endl;
  }

  return 0;
}
