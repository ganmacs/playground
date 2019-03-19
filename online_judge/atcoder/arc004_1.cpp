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

pair<int, int> d[1000];

int main(int argc, char *argv[])
{
  int N, x, y;
  double ans = 0;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    d[i] = make_pair(x, y);
  }

  for (int i = 0; i < N; i++) {
    for (int j = 1; j < N; j++) {
      ans = max(ans, sqrt(pow(d[i].first - d[j].first, 2) + pow(d[i].second - d[j].second, 2)));
    }
  }

  printf("%f\n", ans);
}
