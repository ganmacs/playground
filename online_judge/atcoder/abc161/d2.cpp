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
map<long long, long long> V;

void dfs(long long i) {
  if (3234566667 < i) return;
  if (V[i]) return;
  V[i]++;

  int vv = i%10;

  if (vv > 0) dfs(i*10 + (vv-1));
  dfs(i*10 + vv);
  if (vv < 9) dfs(i*10 + (vv + 1));
}

int main()
{
  int K;
  cin >> K;

  for (int i = 1; i < 10; i++) {
    dfs(i);
  }

  int a = 1;

  for (auto& vi: V) {
    if (a == K) {
      cout << vi.first << endl;
      return 0;
    }
    a++;
  }


  return 0;
}
