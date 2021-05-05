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
#include <numeric>

using namespace std;

int main()
{
  int N, D, H, d, h;

  double  ans = 0;
  vector<pair<int, int >> V;
  cin >> N >> D >> H;
  for (int i = 0; i < N; i++) {
    cin >> d >> h;

    ans = max(ans, (double)-d*(double)(H-h)/(double)(D-d) + (double)h);
  };

  printf("%f\n", ans);
  return 0;
}
