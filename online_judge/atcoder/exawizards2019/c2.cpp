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

int N, Q;
string s;
char t[223456], d[223456];

bool left(int p) {
  for (int i = 0; i < Q; i++) {
    if (t[i] == s[p]) {
      p += ((d[i] == 'L') ? -1 : 1);
    }
    if (p < 0) return true;
  }

  return false;
}

bool right(int p) {
  for (int i = 0; i < Q; i++) {
    if (t[i] == s[p]) {
      p += ((d[i] == 'L') ? -1 : 1);
    }
    if (p >= N) return true;
  }

  return false;
}

int main(int argc, char *argv[])
{

  cin >> N >> Q;
  cin >> s;

  int ans = N;

  for (int i = 0; i < Q; i++) {
    cin >> t[i] >> d[i];
  }

  int ok = 0, ng = N;
  while (abs(ok-ng) > 1) {
    int mid = (ok + ng)/2;
    if (left(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  if (left(ok)) {
    ans -= (ok + 1);
  }

  ok = N-1, ng = -1;
  while (abs(ok-ng) > 1) {
    int mid = (ok + ng)/2;
    if (right(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  if (right(ok)) {
    ans -= N-(ok);
  }

  cout << ans << endl;

  return 0;
}
