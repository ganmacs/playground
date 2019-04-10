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

// N = a + b + c;
// M = 2a + 3b + 4c;
// M-N = a + 2b + 3c
// M-N-2b-3c = a

int S, a,aa, tmp, N, M;
long vv[20000][20000];

bool dfs(int b, int c) {
  if (vv[b][c]) return false;
  vv[b][c] = true;

  tmp = 2*b + 3*c;
  a = S - tmp;
  if (a < 0) return false;

  if (c + b + a == N && 2*a + 3*b + 4*c == M) {
    printf("%d %d %d\n", a, b, c);
    return true;
  } else if (c + b > N){
    return false;
  }

  bool r1 = dfs(b + 1, c);
  if (r1) return true;
  bool r2 = dfs(b, c + 1);

  return r2;
}

int main(int argc, char *argv[])
{
  cin >> N >> M;
  S = M - N;

  if (!dfs(1, 1) && !dfs(1, 0) && !dfs(0, 1) && !dfs(0, 0)) {
    puts("-1 -1 -1");
  }
  return 0;
}
