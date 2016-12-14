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
int v[100], w[100];
int N, W;

int sch(int d, int i)
{
  if (i == N) {
    return 0;
  } else if (d < w[i]) {
    return sch(d, i + 1);
  } else {
    int r1 = sch(d, i + 1);
    int r2 = sch(d - w[i], i + 1) + v[i];
    return max(r1, r2);
  }
}

int main()
{
  cin >> N >> W;
  for (int i = 0; i < N; i++) {
    cin >> v[i] >> w[i];
  }
  cout << sch(W, 0) << endl;
}
