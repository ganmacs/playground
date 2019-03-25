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

int a[20];
int N, k;

int main(int argc, char *argv[])
{
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];
  cin >> k;

  for (int i = 0; i < (1 << N); i++) {
    int v = 0;
    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) v += a[j];
    }

    if (v == k) {
      puts("Yes");
      return 0;
    }
  }

  puts("No");
  // printf("%s\n", dfs(0, 0) ? "Yes" : "No");
  return 0;
}
