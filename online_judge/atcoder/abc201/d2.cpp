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
vector<string> A;

bool visited[2000][2000];
int dp[2000][2000];

int dfs(int i, int j, int t) {
  if (visited[i][j]) return dp[i][j];

  int a = 0;
  if (t % 2 == 0) {
    a = -1e9;
    if (i + 1 < H) a = max(a, dfs(i + 1, j, t + 1) + (A[i + 1][j] == '+' ? 1 : -1));
    if (j + 1 < W) a = max(a, dfs(i, j + 1, t + 1) + (A[i][j + 1] == '+' ? 1 : -1));
  } else {
    a = 1e9;
    if (i + 1 < H) a = min(a, dfs(i + 1, j, t + 1) + (A[i + 1][j] == '+' ? -1 : 1));
    if (j + 1 < W) a = min(a, dfs(i, j + 1, t + 1) + (A[i][j + 1] == '+' ? -1 : 1));
  }

  visited[i][j] = true;
  return dp[i][j] = a;
}

int main()
{
  string s;
  cin >> H >> W;
  for (int i = 0; i < H; i++) {
    cin >> s;
    A.push_back(s);
    fill(visited[i], visited[i] + W, false);
    fill(dp[i], dp[i] + W, 0);
  }

  visited[H-1][W-1] = true;

  auto v = dfs(0, 0, 0);

  if (v == 0) {
    puts("Draw");
  } else if(v > 0) {
    puts("Takahashi");
  } else {
    puts("Aoki");
  }

  return 0;
}
