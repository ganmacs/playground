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

int N, C, a[100], b[100];

map<string, int> Map;
void dfs(int l, int r) {
  if (r == 0) {
    string str = "";
    for (int i = 0; i < C; i++) {
      char v1 = (a[i] % 10) + '0';
      char v2 = (a[i] / 10) + '0';
      if (v2 != '0') {
        str += v2;
      }
      str += v1;
    }
    printf("%s\n", str.c_str());
    Map[str]++;
  } else {
    if (l == N) return;
    dfs(l + 1, r);

    swap(a[r], a[l]);
    dfs(l + 1, r-1);
    swap(a[l], a[r]);
  }
}

int main(int argc, char *argv[])
{
  cin >> N >> C;

  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  dfs(0, C);

  int ans = 0;

  for (auto v: Map) {
    ans++;
    cout << v.first << endl;
  }

  cout << ans << endl;
  return 0;
}
