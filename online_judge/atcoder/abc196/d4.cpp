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

void dfs(long long m, int i, int a, int b) {
  if (i == H*W) {
    ans++;
    return;
  }

  if (m & (1 << i)) {
    dfs(m, i + 1, a, b);
    return;
  }

  if (a) {
    if (i%W != (W-1) && ~m & (1 << (i + 1))) {
      dfs(m | 1 << i | 1 << (i + 1), i + 2, a-1, b);
    }

    if ((i+W) < W*H && ~m & (1 << (i + W))) {
      dfs(m | 1 << i | 1 << (i + W), i + 1, a-1, b);
    }
  }

  if (b) {
    dfs(m | 1 << i , i + 1, a, b-1);
  }
}


int main()
{
  cin >> H >> W >> A >> B;
  dfs(0, 0, A, B);
  cout << ans << endl;
  return 0;
}
