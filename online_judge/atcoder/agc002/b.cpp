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

int main()
{
  int N, M, x, y;
  cin >> N >> M;
  vector<pair<int, int>> V(M);
  vector<int> b1(N, 1);
  vector<bool> red(N, false);
  red[0] = true;

  for (auto& vi: V) {
    cin >> x >> y;
    x--;y--;
    vi = make_pair(x, y);
  }

  for (auto& vi: V) {
    x = vi.first;
    y = vi.second;

    b1[x]--;
    b1[y]++;

    if (red[x]) {
      red[y] = true;
    }

    if (b1[x] == 0) {
      red[x] = false;
    }
  }

  cout << count(red.begin(), red.end(),  true) << endl;
  return 0;
}
