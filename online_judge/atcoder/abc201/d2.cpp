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
vector<string> V;
int M[2001][2001];
bool used[2001][2001];

int dfs(int i, int j) {
  if (used[i][j]) return M[i][j];

  int ta;
  if ((i + j) % 2 == 0) {
    ta = -1e9;
    if (i + 1 < H) ta = max(ta, dfs(i + 1, j) + (V[i + 1][j] == '+' ? 1 : -1));
    if (j + 1 < W) ta = max(ta, dfs(i, j + 1) + (V[i][j + 1] == '+' ? 1 : -1));
  } else {
    ta = 1e9;
    if (i + 1 < H) ta = min(ta, dfs(i + 1, j) + (V[i + 1][j] == '+' ? -1 : 1));
    if (j + 1 < W) ta = min(ta, dfs(i, j + 1) + (V[i][j + 1] == '+' ? -1 : 1));
  }

  used[i][j] = true;
  return (M[i][j] = ta);
}

int main()
{
  cin >> H >> W;
  string s;
  for (int i = 0; i < H; i++) {
    cin >> s;
    V.push_back(s);
    fill(used[i], used[i] + W, false);
    fill(M[i], M[i] + W, 0);
  }
  used[H-1][W-1] = true;

  auto v = dfs(0, 0);
  if (v > 0) {
    cout << "Takahashi\n";
  } else if (v < 0){
    cout << "Aoki\n";
  } else {
    cout << "Draw\n";
  }
  return 0;
}
