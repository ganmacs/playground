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

int H, W, A, B, ans = 0;
bool D[19];

void dfs(int j, int a, int b)
{
  if (j == H*W) {
    ans++;
    return;
  }

  if (D[j]) {
    dfs(j + 1, a, b);
    return;
  }

  D[j] = true;
  if (a < A) {
    if ((((j + 1) / W) == (j / W)) && !D[j + 1]) {
      D[j + 1] = true;
      dfs(j + 1, a + 1, b);
      D[j + 1] = false;
    }

    if ((j+W) < H*W && !D[j + W]) {
      D[j + W] = true;
      dfs(j + 1, a + 1, b);
      D[j + W] = false;
    }
  }

  if (b < B) {
    dfs(j + 1, a, b + 1);
  }

  D[j] = false;
}

int main()
{
  cin >> H >> W >> A >> B;
  fill(D, D + H*W, false);
  dfs(0, 0, 0);
  cout << ans << endl;
  return 0;
}
