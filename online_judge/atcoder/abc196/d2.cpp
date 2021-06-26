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

void dfs(int i, long long bit, int a, int b) {
  if (i == H*W) {
    ans++;
    return;
  }

  if (bit & (1 << i)) {
    dfs(i + 1, bit, a, b);
    return;
  }

  bit |= (1 << i);

  if (a) {
    if ((i + 1) <= H*W && ((i + 1) % W) != 0 && (~bit & 1 << (i + 1))) {
      dfs(i + 1, bit | (1 << (i + 1)), a-1, b);
    }

    if ((i + W) <= (W*H)) {
      dfs(i + 1, bit | (1 << (i + W)), a-1, b);
    }
  }

  if (b) {
    dfs(i + 1, bit, a, b-1);
  }
}

int main()
{
  cin >> H >> W >> A >> B;
  dfs(0, 0, A, B);
  cout << ans << endl;
  return 0;
}
