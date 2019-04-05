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

long long ans[123456];
int N, W;
long long w, v;

int main(int argc, char *argv[])
{
  cin >> N >> W;
  std::fill(ans, ans + W, 0);
  for (int i = 0; i < N; i++) {
    cin >> w >> v;

    for (int j = W; j >= w; j--) {
      ans[j] = max(ans[j-w] + v, ans[j]);
    }
  }
  cout << ans[W] << endl;
  return 0;
}
