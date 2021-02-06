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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  bool G[20][20] = {};
  int N, M, a, b;
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    a-- , b--;
    G[a][b] = G[b][a] = true;
  }

  int ret = 1;
  for (int i = 0; i < (1<<N); i++) {
    bool ok = true;
    for (int j = 0; j < N && ok; j++) {
      for (int k = j + 1; k < N && ok; k++) {
        if  ((i&(1<<j)) && (i&(1<<k)) && !G[j][k]) {
          ok = false;
        }
      }
    }

    if (ok) {
      int v = 0;
      for (int j = 0; j < N; j++) {
        if (i&(1<<j)) v++;
      }

      ret = max(ret, v);
    }
  }

  cout << ret << endl;
  return 0;
}
