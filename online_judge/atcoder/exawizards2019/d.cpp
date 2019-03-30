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

int N, X;
long long vv[200], s[123456], ans = 0;

void dfs(long long v, int i, long long c) {
  if (v < s[i + 1]) {
    ans += (vv[N-i]*v) % (1000000000LL + 9);
  } else {
    long long kkk = c % v;
    if (s[i + 1] > kkk) {
      ans += vv[i + 1]*kkk;
    } else {
      dfs(10, i + 1, kkk)
    }
  }
}

int main(int argc, char *argv[])
{

  cin >> N >> X;
  vv[1] = 1;
  for (int i = 2; i < N; i++) {
    vv[i] = (i*vv[i-1]) % (1000000000LL + 9);
  }

  for (int i = 0; i < N; i++) {
    cin >> s[i];
  }

  sort(s, s + N);


  for (int i = 0; i < N-1; i++) {
    long long v = X % s[i];
    if (v < s[i + 1]) {
      ans += (vv[N- i + 1]*v) % (1000000000LL + 9);
      break;
    } else {
    }
  }

  cout << ans << endl;
  return 0;
}
