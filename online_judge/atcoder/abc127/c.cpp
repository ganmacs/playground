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

int main(int argc, char *argv[])
{
  int N, M;
  int l = 0, r = 123456, ll, rr;
  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    cin >> ll >> rr;
    l = max(ll, l);
    r = min(rr, r);
  }

  if (l > r) {
    cout << 0 << endl;
    return 0;
  }

  cout << min(r, N) - (l - 1) << endl;

  return 0;
}
